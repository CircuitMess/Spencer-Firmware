#include "WeatherIntent.h"
#include <NTPClient.h>
#include <string>
#include <ArduinoJson.h>
#include "../Services/LocationService/LocationService.h"
#include "../Services/TimeService/TimeService.h"
#include "../Services/Audio/Playback.h"
#include "../LEDmatrix/LEDmatrix.h"
#include <Util/Task.h>
#include "../State/ErrorState.h"
#include "../Settings.h"

#define CA "DC:03:B5:D6:0C:F1:02:F1:B1:D0:62:27:9F:3E:B4:C3:CD:C9:93:BA:20:65:6D:06:DC:5D:56:AC:CC:BA:40:20"
WeatherIntent* WeatherIntent::instance = nullptr;

WeatherIntent::WeatherIntent(WeatherIntentParam value)
{
	instance = this;
	params = value;
	fetchTask = new Task("WeatherFetch", [](Task* task){
		instance->doneFetching = false;
		if(!Net.checkConnection()){
			if(!Net.reconnect()){
				instance->doneFetching = true;
				instance->result = new WeatherResult{ WeatherResult::NETWORK, 0, 0, 0};
				return;
			}
		}
		if(instance == nullptr) return;
		switch (instance->params)
		{
		case WeatherIntentParam::TODAY:
			if(instance == nullptr) return;
			instance->currentWeather();
			break;
		case WeatherIntentParam::TOMORROW:
			if(instance == nullptr) return;
			instance->tomorrowForecast();
			break;
		case WeatherIntentParam::WEEK:
			if(instance == nullptr) return;
			instance->weeklyForecast();
			break;
		default:
			break;
		}
		if(instance == nullptr) return;
		instance->doneFetching = true;

	}, 8192);
	fetchTask->start(1, 0);
}

WeatherIntent::~WeatherIntent()
{
	delete result;
	delete fetchTask;
	instance = nullptr;
}

void WeatherIntent::loop(uint _time)
{
	if(doneFetching){
		if(result != nullptr){
			switch (result->error)
			{
			case WeatherResult::OK:
				switch (instance->params)
				{
				case WeatherIntentParam::TODAY:
					generateOutput(result->temperature, result->weatherCode, result->dayNight, 0);
					break;
				case WeatherIntentParam::TOMORROW:
					generateOutput(result->temperature, result->weatherCode, result->dayNight, 1);
					break;
				case WeatherIntentParam::WEEK:
					generateWeeklyDay();
					break;
				default:
					break;
				}

				delete result;
				result = nullptr;
				break;

			case WeatherResult::NETWORK:
				if(networkRetry){
					State::changeState(new ErrorState(ErrorType::NETWORK));
					return;
				}

				networkRetry = true;
				fetchTask->start(1, 0);
				break;
			
			case WeatherResult::JSON:
				State::changeState(new ErrorState(ErrorType::JSON));
				return;

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
	sprintf(url, "https://spencer.circuitmess.com:8443/weather/data/2.5/weather?lon=%.6f&lat=%.6f", LocationService.getLocation()->lon, LocationService.getLocation()->lat);

	bool httpOK = http.begin(url, CA);
	free(url);
	if(!httpOK){
		http.end();
		http.getStream().stop();
		http.getStream().flush();

		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}

	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		http.end();
		http.getStream().stop();
		http.getStream().flush();

		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}

	const int SIZE = JSON_OBJECT_SIZE(6) + 50;
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, http.getStream());

	if(error){
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}
	
	int temp = roundl(json["temp"].as<float>() - 273.15);
	bool dayNight = json["night"].as<bool>();
	uint16_t weatherCode = json["code"].as<int>();

	if(Settings.get().fahrenheit){
		temp = round((float) temp * 1.8f + 32.0f);
	}
	
	if(instance == nullptr) return;
	instance->result = new WeatherResult{WeatherResult::OK, temp, weatherCode, dayNight};
}
void WeatherIntent::tomorrowForecast()
{
	//location info request
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	char *url = (char*)calloc(150, sizeof(char));
	sprintf(url, "https://spencer.circuitmess.com:8443/weather/data/2.5/forecast/daily?lon=%.6f&lat=%.6f", LocationService.getLocation()->lon, LocationService.getLocation()->lat);
	bool httpOK = http.begin(url, CA);
	free(url);
	if(!httpOK){
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}
	http.addHeader("Scope", "Tomorrow");
	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}

	const int SIZE = JSON_OBJECT_SIZE(6) + 50;
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, http.getStream());

	if(error){
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}

	int temp = roundl(json["temp"].as<float>() - 273.15);
	bool dayNight = json["night"].as<boolean>();
	uint16_t weatherCode = json["code"].as<int>();

	if(Settings.get().fahrenheit){
		temp = round((float) temp * 1.8f + 32.0f);
	}

	if(instance == nullptr) return;
	instance->result = new WeatherResult{WeatherResult::OK, temp, weatherCode, dayNight};

}
void WeatherIntent::weeklyForecast()
{
	//location info request
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	char *url = (char*)calloc(150, sizeof(char));
	sprintf(url, "https://spencer.circuitmess.com:8443/weather/data/2.5/forecast/daily?lon=%.6f&lat=%.6f&cnt=8", LocationService.getLocation()->lon, LocationService.getLocation()->lat);
	bool httpOK = http.begin(url, CA);
	free(url);
	if(!httpOK){
		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}
	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::NETWORK};
		return;
	}

	const int SIZE = JSON_ARRAY_SIZE(6) + 6*JSON_OBJECT_SIZE(4) + 50;
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, http.getStream());

	if(error){
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		if(instance == nullptr) return;
		instance->result = new WeatherResult{WeatherResult::JSON};
		return;
	}

	for(uint8_t i = 0; i < 6; i++)
	{
		weeklyTemp[i] = roundl(json.getElement(i)["temp"].as<float>() - 273.15);
		weeklyDayNight[i] = json.getElement(i)["night"].as<boolean>();
		weeklyWeatherCode[i] = json.getElement(i)["code"].as<int>();
	}

	http.end();
	http.getStream().stop();
	http.getStream().flush();

	if(instance == nullptr) return;
	instance->result = new WeatherResult{WeatherResult::OK};
	instance->weeklyIndex = 0;
}

void WeatherIntent::enter()
{

}

void WeatherIntent::exit()
{

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
	tempSpeak->add(SampleStore::load(SampleGroup::Weather, Settings.get().fahrenheit ? "fahrenheit" : "celsius"));

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
		if(instance == nullptr) return;
		Playback.playMP3(instance->weatherSpeak);
		Playback.setPlaybackDoneCallback([](){
			if(instance == nullptr) return;
			instance->weeklyIndex++;
			instance->generateWeeklyDay();
		});
		LEDmatrix.startAnimation(instance->weatherAnimation, 1);
	});
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
	tempSpeak->add(SampleStore::load(SampleGroup::Weather, Settings.get().fahrenheit ? "fahrenheit" : "celsius"));

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
	LEDmatrix.stopAnimation();
	LEDmatrix.clear();
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
		if(instance == nullptr) return;
		LEDmatrix.startAnimation(instance->weatherAnimation, 1);
		Playback.playMP3(instance->weatherSpeak);
		Playback.setPlaybackDoneCallback([](){
			if(instance == nullptr) return;
			done();
		});
	});
}
