#include "WeatherIntent.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <string>
#include <ArduinoJson.h>
#include "../Services/LocationService/LocationService.h"
#include "../Services/Audio/Playback.h"
#include "../LEDmatrix/LEDmatrix.h"
#define CA "EB:6D:04:1A:C9:07:50:C7:52:C5:BC:69:E0:79:87:A6:5A:E5:2F:A8:23:D7:93:52:8C:9F:E8:62:27:AB:65:47"
#define KEY "1f8e6989d4d112dc861b2853adc76265"
WeatherIntent* WeatherIntent::instance = nullptr;

WeatherIntent::WeatherIntent(void* _params)
{
	instance = this;
	params = *static_cast<WeatherIntentParam*>(_params);

	if(params.time == nullptr){
		currentWeather();
	}else if(strcmp(params.time, "today") == 0){
		currentWeather();
	}else if(strcmp(params.time, "tomorrow") == 0){
		tomorrowForecast();
	}else if(strcmp(params.time, "this week") == 0){
		weeklyForecast();
	}
}

WeatherIntent::~WeatherIntent()
{
}

void WeatherIntent::loop(uint _time)
{

}

bool WeatherIntent::currentWeather()
{
	//location info request
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	char url[150];
	sprintf(url, "https://api.openweathermap.org/data/2.5/weather?appid=%s&lon=%.6f&lat=%.6f", KEY, LocationService.getLocation()->lon, LocationService.getLocation()->lat);
	Serial.println(url);
	http.begin(url, CA);
	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		return false;
	}

	for(uint8_t i = 0; i < 3; i++)
	{
		if(!http.getStream().find('{')) return false;
	}
	char *buffer = (char*)calloc(200, sizeof(char));
	buffer[0]='{';
	int readBytes = http.getStream().readBytesUntil('}', buffer + 1, 200);
	buffer[readBytes + 1] = '}';

	const int SIZE = JSON_OBJECT_SIZE(6);
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, buffer);
	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		return false;
	}
	bool dayNight = json["icon"].as<char*>()[2] == 'n'; //day - 0, night - 1
	uint16_t weatherCode = json["id"].as<int>(); //weather code

	if(!http.getStream().find(']')) return false;
	if(!http.getStream().find('{')) return false;
	memset(buffer, 0, 200);
	buffer[0]='{';
	readBytes = http.getStream().readBytesUntil('}', buffer + 1, 200);
	buffer[readBytes + 1] = '}';
	error = deserializeJson(json, buffer);
	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		return false;
	}
	serializeJsonPretty(json, Serial);
	
	int temp = roundl(json["temp"].as<float>() - 273.15);
	Serial.println(temp);
	int feelsLike = roundl(json["feels_like"].as<float>() - 273.15);

	http.end();
	http.getStream().stop();
	http.getStream().flush();
	CompositeAudioFileSource *tempSpeak = new CompositeAudioFileSource();
	tempSpeak->add(SampleStore::load(SampleGroup::Weather, "temperature_is"));
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
				weatherSpeak = SampleStore::load(SampleGroup::Weather, "clear");
				weatherAnimation = new Animation("GIF-night.gif");
			}else{
				weatherSpeak = SampleStore::load(SampleGroup::Weather, "sunny");
				weatherAnimation = new Animation("GIF-sun.gif");
			}
			//sunny/clear sky
		}else{
			weatherSpeak = SampleStore::load(SampleGroup::Weather, "cloudy");
			weatherAnimation = new Animation("GIF-clouds.gif");
			//cloudy
		}
		
		break;
	
	case 7:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, "foggy");
		weatherAnimation = new Animation("GIF-fog.gif");
		//foggy	
		break;

	case 6:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, "snowy");
		weatherAnimation = new Animation("GIF-snow.gif");
		//snowy
		break;
	
	default:
		weatherSpeak = SampleStore::load(SampleGroup::Weather, "rainy");
		weatherAnimation = new Animation("GIF-rain.gif");
		//rainy, 2 - thunderstorm, 3 - drizzle, 5 - rain
		break;
	}
	LEDmatrix.clear();
	sprintf(buff, "%d", temp);
	if(temp > 0 && temp < 10){
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
	});

}

bool WeatherIntent::tomorrowForecast()
{
	
}

bool WeatherIntent::weeklyForecast()
{
	
}


