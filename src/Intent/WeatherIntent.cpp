#include "WeatherIntent.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <string>
#include <ArduinoJson.h>
#include "../Services/LocationService/LocationService.h"
#include "../Services/TimeService/TimeService.h"
#include "../Services/Audio/Playback.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Net.h"
#include <Util/Task.h>
#include "../State/SetupState.h"
#include "../State/IdleState.h"
#include "../State/State.h"

#define CA "EB:6D:04:1A:C9:07:50:C7:52:C5:BC:69:E0:79:87:A6:5A:E5:2F:A8:23:D7:93:52:8C:9F:E8:62:27:AB:65:47"
#define KEY "1f8e6989d4d112dc861b2853adc76265"
WeatherIntent* WeatherIntent::instance = nullptr;

WeatherIntent::WeatherIntent(void* _params)
{
	instance = this;
	params = *static_cast<WeatherIntentParam*>(_params);
	fetchTask = new Task("WeatherFetch", [](Task* task){
		instance->doneFetching = false;
		if(!Net.checkConnection()){
			if(!Net.reconnect()){
				instance->doneFetching = true;
				instance->result = new WeatherResult{ WeatherResult::NETWORK, 0, 0, 0};
				return;
			}
		}
		if(instance->params.time == nullptr){
			instance->currentWeather();
		}else if(strcmp(instance->params.time, "today") == 0){
			instance->currentWeather();
		}else if(strcmp(instance->params.time, "tomorrow") == 0){
			instance->tomorrowForecast();
		}else if(strcmp(instance->params.time, "this week") == 0){
			instance->weeklyForecast();
		}
		instance->doneFetching = true;

	}, 8000);
	fetchTask->start(1, 0);
}

WeatherIntent::~WeatherIntent()
{
	delete fetchTask;
}

void WeatherIntent::loop(uint _time)
{
	if(doneFetching){
		if(result != nullptr){
			switch (result->error)
			{
			case WeatherResult::OK:
				if(instance->params.time == nullptr){
					generateOutput(result->temperature, result->weatherCode, result->dayNight, 0);
				}else if(strcmp(instance->params.time, "today") == 0){
					generateOutput(result->temperature, result->weatherCode, result->dayNight, 0);
				}else if(strcmp(instance->params.time, "tomorrow") == 0){
					generateOutput(result->temperature, result->weatherCode, result->dayNight, 1);
				}else if(strcmp(instance->params.time, "this week") == 0){
					generateWeeklyDay();
				}
				delete result;
				result = nullptr;
				break;

			case WeatherResult::NETWORK:
				delete result;
				result = nullptr;
				if(networkRetry){
					LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
					Playback.playMP3(SampleStore::load(Generic, "noNet"));
					Playback.setPlaybackDoneCallback([](){
						State::changeState(new SetupState());
					});
					return;
				}
				networkRetry = true;
				fetchTask = new Task("WeatherFetch", [](Task* task){
					instance->doneFetching = false;
					if(!Net.checkConnection()){
						if(!Net.reconnect()){
							instance->doneFetching = true;
							instance->result = new WeatherResult{ WeatherResult::NETWORK, 0, 0, 0};
							return;
						}
					}
					if(instance->params.time == nullptr){
						instance->currentWeather();
					}else if(strcmp(instance->params.time, "today") == 0){
						instance->currentWeather();
					}else if(strcmp(instance->params.time, "tomorrow") == 0){
						instance->tomorrowForecast();
					}else if(strcmp(instance->params.time, "this week") == 0){
						instance->weeklyForecast();
					}
					instance->doneFetching = true;
				}, 8000);
				fetchTask->start(1, 0);
				break;
			
			case WeatherResult::JSON:
				LEDmatrix.startAnimation(new Animation("GIF-error500.gif"), true);
				Playback.playMP3("generic-mess.mp3");
				delete result;
				result = nullptr;
				Playback.setPlaybackDoneCallback([](){
					State::changeState(new IdleState());
				});
				break;
			default:
				break;
			}
		}
	}
}

void WeatherIntent::currentWeather()
{
	//location info request
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	char *url = (char*)calloc(150, sizeof(char));
	sprintf(url, "https://api.openweathermap.org/data/2.5/weather?appid=%s&lon=%.6f&lat=%.6f", KEY, LocationService.getLocation()->lon, LocationService.getLocation()->lat);

	bool httpOK = http.begin(url, CA);
	free(url);
	if(!httpOK){
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}
	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}

	for(uint8_t i = 0; i < 3; i++)
	{
		if(!http.getStream().find('{')){
			instance->result = new WeatherResult{WeatherResult::JSON};
			return;
		}
	}
	char *buffer = (char*)calloc(200, sizeof(char));
	buffer[0]='{';
	int readBytes = http.getStream().readBytesUntil('}', buffer + 1, 200);
	buffer[readBytes + 1] = '}';

	const int SIZE = JSON_OBJECT_SIZE(6);
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, buffer);
	if(error){
		free(buffer);
		json.clear();
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}
	bool dayNight = json["icon"].as<char*>()[2] == 'n'; //day - 0, night - 1
	uint16_t weatherCode = json["id"].as<int>(); //weather code

	if(!http.getStream().find(']')){
		json.clear();
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}
	if(!http.getStream().find('{')){
		json.clear();
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}
	memset(buffer, 0, 200);
	buffer[0]='{';
	readBytes = http.getStream().readBytesUntil('}', buffer + 1, 200);
	http.end();
	http.getStream().stop();
	http.getStream().flush();
	buffer[readBytes + 1] = '}';
	error = deserializeJson(json, buffer);
	free(buffer);
	
	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		instance->result = new WeatherResult{WeatherResult::JSON};
		json.clear();
		return;
	}
	// serializeJsonPretty(json, Serial);
	
	int temp = roundl(json["temp"].as<float>() - 273.15);
	int feelsLike = roundl(json["feels_like"].as<float>() - 273.15);

	json.clear();
	
	instance->result = new WeatherResult{WeatherResult::OK, temp, weatherCode, dayNight};
}
void WeatherIntent::generateOutput(int temp, uint16_t weatherCode, bool dayNight, bool forecast)
{
	CompositeAudioFileSource *tempSpeak = new CompositeAudioFileSource();
	tempSpeak->add(SampleStore::load(SampleGroup::Weather, forecast ? "forecast" : "temperature_is"));
	if(temp < 0){
		tempSpeak->add(SampleStore::load(SampleGroup::Weather, "minus"));
	}
	char buff[7];
	if((abs(temp)) > 19){
		sprintf(buff, "%d", ((abs(temp)) / 10)*10);
		tempSpeak->add(SampleStore::load(SampleGroup::Numbers, buff));
		if((abs(temp))%10 > 0){
			sprintf(buff, "%d", (abs(temp)) % 10);
			tempSpeak->add(SampleStore::load(SampleGroup::Numbers, buff));
		}
	}
	else{
		sprintf(buff, "%d", (abs(temp)));
		tempSpeak->add(SampleStore::load(SampleGroup::Numbers, buff));
	}
	tempSpeak->add(SampleStore::load(SampleGroup::Weather, "celsius"));

	switch (weatherCode/100)
	{
	case 8:
		if(weatherCode == 800){
			if(dayNight){
				weatherSpeak = SampleStore::load(SampleGroup::Weather, forecast ? "forecastClear" : "clear");
				weatherAnimation = new Animation("GIF-night.gif");
			}else{
				weatherSpeak = SampleStore::load(SampleGroup::Weather, forecast ? "forecastSunny" : "sunny");
				weatherAnimation = new Animation("GIF-sun.gif");
			}
			//sunny/clear sky
		}else{
			weatherSpeak = SampleStore::load(SampleGroup::Weather, forecast ? "forecastCloudy" : "cloudy");
			if(weatherCode == 801){
				weatherAnimation = new Animation("GIF-sunClouds.gif");
			}else{
				weatherAnimation = new Animation("GIF-clouds.gif");
			}
			//cloudy
		}
		
		break;
	
	case 7:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, forecast ? "forecastFoggy" : "foggy");
		weatherAnimation = new Animation("GIF-fog.gif");
		//foggy	
		break;

	case 6:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, forecast ? "forecastSnowy" : "snowy");
		weatherAnimation = new Animation("GIF-snow.gif");
		//snowy
		break;
	
	default:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, forecast ? "forecastRainy" : "rainy");
		weatherAnimation = new Animation("GIF-rain.gif");
		//rainy, 2 - thunderstorm, 3 - drizzle, 5 - rain
		break;
	}
	LEDmatrix.clear();
	LEDmatrix.stopAnimation();
	sprintf(buff, "%d", temp);
	if(temp >= 0 && temp < 10){
		LEDmatrix.drawString(10,1, buff);
	}else if(temp < -10){
		LEDmatrix.drawString(-2,1, buff);
	}else if(temp < 0){
		LEDmatrix.drawString(4,1, buff);
	}else{
		LEDmatrix.drawString(3,1, buff);
	}
	Playback.playMP3(tempSpeak);
	Playback.setPlaybackDoneCallback([](){
		Playback.playMP3(instance->weatherSpeak);
		LEDmatrix.startAnimation(instance->weatherAnimation, 1);
		Playback.setPlaybackDoneCallback([](){
			instance->done();
			return;
		});
	});
}
void WeatherIntent::tomorrowForecast()
{
	//location info request
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	char *url = (char*)calloc(150, sizeof(char));
	sprintf(url, "https://api.openweathermap.org/data/2.5/forecast/daily?appid=%s&lon=%.6f&lat=%.6f&cnt=7", KEY, LocationService.getLocation()->lon, LocationService.getLocation()->lat);
	bool httpOK = http.begin(url, CA);
	free(url);
	if(!httpOK){
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}
	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}

	if(!http.getStream().find('[')){
		instance->result = new WeatherResult{WeatherResult::JSON};
			return;
	} //"list":
	for(uint8_t i = 0; i < 3; i++){
		if(!http.getStream().find('{')){
			instance->result = new WeatherResult{WeatherResult::JSON};
			return;
		}
	}
	if(!http.getStream().find(']')){
		instance->result = new WeatherResult{WeatherResult::JSON};
			return;
	}
	for(uint8_t i = 0; i < 2; i++){
		if(!http.getStream().find('{')){
			instance->result = new WeatherResult{WeatherResult::JSON};
			return;
		}//"temp" for tomorrow
	}

	char *buffer = (char*)calloc(230, sizeof(char));
	buffer[0]='{';
	int readBytes = http.getStream().readBytesUntil('}', buffer + 1, 230);
	buffer[readBytes + 1] = '}';

	const int SIZE = JSON_OBJECT_SIZE(6);
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, buffer);
	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}
	int temp = roundl(json["day"].as<float>() - 273.15);

	if(!http.getStream().find('[')){
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	} //"weather":
	if(!http.getStream().find('{')){
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	} //first weather element
	

	memset(buffer, 0, 230);
	buffer[0]='{';
	readBytes = http.getStream().readBytesUntil('}', buffer + 1, 230);
	http.end();
	http.getStream().stop();
	http.getStream().flush();
	buffer[readBytes + 1] = '}';
	error = deserializeJson(json, buffer);
	free(buffer);
	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}
	bool dayNight = json["icon"].as<char*>()[2] == 'n'; //day - 0, night - 1
	uint16_t weatherCode = json["id"].as<int>(); //weather code
	json.clear();

	instance->result = new WeatherResult{WeatherResult::OK, temp, weatherCode, dayNight};

}

void WeatherIntent::weeklyForecast()
{
	//location info request
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	char *url = (char*)calloc(150, sizeof(char));
	sprintf(url, "https://api.openweathermap.org/data/2.5/forecast/daily?appid=%s&lon=%.6f&lat=%.6f&cnt=8", KEY, LocationService.getLocation()->lon, LocationService.getLocation()->lat);
	bool httpOK = http.begin(url, CA);
	free(url);
	if(!httpOK){
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}
	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}

	if(!http.getStream().find('[')){
		instance->result = new WeatherResult{WeatherResult::JSON};
		return; //"list":
	}
	for(uint8_t i = 0; i < 3; i++){
		if(!http.getStream().find('{')){
			instance->result = new WeatherResult{WeatherResult::JSON};
			return;
		}
	}
	if(!http.getStream().find(']')){
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}
	for(uint8_t i = 0; i < 2; i++){
		if(!http.getStream().find('{')){
			instance->result = new WeatherResult{WeatherResult::JSON};
			return;//"temp" for tomorrow
		}
	}
	char *buffer = (char*)calloc(230, sizeof(char));
	int readBytes = 0;
	const int SIZE = JSON_OBJECT_SIZE(6);
	DynamicJsonDocument json(SIZE);
	DeserializationError error;
	

	for(uint8_t i = 0; i < 7; i++)
	{
		memset(buffer, 0, 230);
		buffer[0]='{';
		readBytes = http.getStream().readBytesUntil('}', buffer + 1, 230);
		buffer[readBytes + 1] = '}';

		error = deserializeJson(json, buffer);
		if(error){
			Serial.print(F("Parsing JSON failed: "));
			Serial.println(error.c_str());
			instance->result = new WeatherResult{WeatherResult::JSON};
			return;
		}
		weeklyTemp[i] = roundl(json["day"].as<float>() - 273.15);


		if(!http.getStream().find('[')){
			instance->result = new WeatherResult{WeatherResult::JSON};
			return; //"weather":
		}
		if(!http.getStream().find('{')){
			instance->result = new WeatherResult{WeatherResult::JSON};
			return; //first weather element
		}

		memset(buffer, 0, 230);
		buffer[0]='{';
		readBytes = http.getStream().readBytesUntil('}', buffer + 1, 230);
		buffer[readBytes + 1] = '}';
		error = deserializeJson(json, buffer);
		if(error){
			Serial.print(F("Parsing JSON failed: "));
			Serial.println(error.c_str());
			instance->result = new WeatherResult{WeatherResult::JSON};
			return;
		}
		weeklyDayNight[i] = json["icon"].as<char*>()[2] == 'n'; //day - 0, night - 1
		weeklyWeatherCode[i] = json["id"].as<int>(); //weather code

		if(i < 6){
			if(!http.getStream().find(']')){
				instance->result = new WeatherResult{WeatherResult::JSON};
				return;
			} //end of "weather":
			for(uint8_t i = 0; i < 2; i++){
				if(!http.getStream().find('{')){
					instance->result = new WeatherResult{WeatherResult::JSON};
					return;
				}//"temp" for next day
			}
		}
	}
	json.clear();
	free(buffer);
	http.end();
	http.getStream().stop();
	http.getStream().flush();
	weeklyIndex = 0;
	instance->result = new WeatherResult{WeatherResult::OK};

}

void WeatherIntent::generateWeeklyDay()
{
	if(weeklyIndex > 6){
		done();
		return;
	}

	CompositeAudioFileSource* tempSpeak = new CompositeAudioFileSource();
	char buff[7];
	uint8_t currentDay = DateTime(TimeService.getTime()).dayOfTheWeek() + weeklyIndex + 1;
	if(currentDay > 7){
		currentDay-=7;
	}
	sprintf(buff, "%d", currentDay);
	tempSpeak->add(SampleStore::load(SampleGroup::Weekdays, buff));
	tempSpeak->add(SampleStore::load(SampleGroup::Weather, "forecast"));
	if(weeklyTemp[weeklyIndex] < 0){
		tempSpeak->add(SampleStore::load(SampleGroup::Weather, "minus"));
	}
	if((abs(weeklyTemp[weeklyIndex])) > 19){
		sprintf(buff, "%d", ((abs(weeklyTemp[weeklyIndex])) / 10)*10);
		tempSpeak->add(SampleStore::load(SampleGroup::Numbers, buff));
		if((abs(weeklyTemp[weeklyIndex]))%10 > 0){
			sprintf(buff, "%d", (abs(weeklyTemp[weeklyIndex])) % 10);
			tempSpeak->add(SampleStore::load(SampleGroup::Numbers, buff));
		}
	}
	else{
		sprintf(buff, "%d", (abs(weeklyTemp[weeklyIndex])));
		tempSpeak->add(SampleStore::load(SampleGroup::Numbers, buff));
	}
	tempSpeak->add(SampleStore::load(SampleGroup::Weather, "celsius"));

	switch (weeklyWeatherCode[weeklyIndex]/100)
	{
	case 8:
		if(weeklyWeatherCode[weeklyIndex] == 800){
			if(weeklyDayNight[weeklyIndex]){
				weatherSpeak = SampleStore::load(SampleGroup::Weather, "forecastClear");
				weatherAnimation = new Animation("GIF-night.gif");
			}else{
				weatherSpeak = SampleStore::load(SampleGroup::Weather, "forecastSunny");
				weatherAnimation = new Animation("GIF-sun.gif");
			}
			//sunny/clear sky
		}else{
			weatherSpeak = SampleStore::load(SampleGroup::Weather, "forecastCloudy");
			if(weeklyWeatherCode[weeklyIndex] == 801){
				weatherAnimation = new Animation("GIF-sunClouds.gif");
			}else{
				weatherAnimation = new Animation("GIF-clouds.gif");
			}
			//cloudy
		}
		
		break;
	
	case 7:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, "forecastFoggy");
		weatherAnimation = new Animation("GIF-fog.gif");
		//foggy	
		break;

	case 6:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, "forecastSnowy");
		weatherAnimation = new Animation("GIF-snow.gif");
		//snowy
		break;
	
	default:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, "forecastRainy");
		weatherAnimation = new Animation("GIF-rain.gif");
		//rainy, 2 - thunderstorm, 3 - drizzle, 5 - rain
		break;
	}
	LEDmatrix.stopAnimation();
	LEDmatrix.clear();
	sprintf(buff, "%d", weeklyTemp[weeklyIndex]);
	if(weeklyTemp[weeklyIndex] >= 0 && weeklyTemp[weeklyIndex] < 10){
		LEDmatrix.drawString(10,1, buff);
	}else if(weeklyTemp[weeklyIndex] < -10){
		LEDmatrix.drawString(-2,1, buff);
	}else if(weeklyTemp[weeklyIndex] < 0){
		LEDmatrix.drawString(4,1, buff);
	}else{
		LEDmatrix.drawString(3,1, buff);
	}
	Playback.playMP3(tempSpeak);
	Playback.setPlaybackDoneCallback([](){
		Playback.playMP3(instance->weatherSpeak);
		Playback.setPlaybackDoneCallback([](){
			Serial.printf("next callback set: %d\n", instance->weeklyIndex);
			instance->weeklyIndex++;
			instance->generateWeeklyDay();
		});
		LEDmatrix.startAnimation(instance->weatherAnimation, 1);
	});
}

void WeatherIntent::enter()
{

}
void WeatherIntent::exit()
{
	
}