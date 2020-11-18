#ifndef SPENCER_WEATHER_H
#define SPENCER_WEATHER_H

#include <Arduino.h>
#include "Intent.hpp"
class AudioFileSource;
class Animation;

struct WeatherIntentParam
{
	const char* time;
	const char* location;
};

class WeatherIntent : public Intent
{
public:
	WeatherIntent(void* params);
	virtual ~WeatherIntent() override;
	void loop(uint micros) override;

private:
	WeatherIntentParam params;
	bool currentWeather();
	bool tomorrowForecast();
	bool weeklyForecast();
	void generateWeeklyDay();
	static WeatherIntent* instance;
	AudioFileSource* weatherSpeak;
	Animation* weatherAnimation;
	int8_t weeklyIndex = -1;
	int weeklyTemp[7] = {0};
	uint16_t weeklyWeatherCode[7] = {0};
	bool weeklyDayNight[7] = {0};
	AudioFileSource* weeklyTempSpeak[7] = {0};
};


#endif