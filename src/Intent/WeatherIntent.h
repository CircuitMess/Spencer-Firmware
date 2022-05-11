#ifndef SPENCER_WEATHER_H
#define SPENCER_WEATHER_H

#include <Arduino.h>
#include "Intent.hpp"

class AudioFileSource;
class MatrixAnimGIF;
class Task;

enum WeatherIntentParam{ TODAY, TOMORROW, WEEK};
struct WeatherResult {
	enum { OK = 0, NETWORK, JSON} error;
	int temperature;
	uint16_t weatherCode;
	bool dayNight;
};
class WeatherIntent : public Intent
{
public:
	WeatherIntent(WeatherIntentParam value);
	virtual ~WeatherIntent() override;
	void loop(uint micros) override;
	void enter() override;
	void exit() override;

private:
	static WeatherIntent* instance;
	WeatherIntentParam params;

	void currentWeather();
	void tomorrowForecast();
	void weeklyForecast();
	void generateWeeklyDay();
	void generateOutput(int temp, uint16_t weatherCode, bool dayNight, bool forecast = 0);
	
	AudioFileSource* weatherSpeak = nullptr;
	MatrixAnimGIF* weatherAnimation = nullptr;

	int8_t weeklyIndex = -1;
	int weeklyTemp[7] = {0};
	uint16_t weeklyWeatherCode[7] = {0};
	bool weeklyDayNight[7] = {0};
	AudioFileSource* weeklyTempSpeak[7] = {0};

	Task* fetchTask = nullptr;
	bool doneFetching = false;
	WeatherResult *result = nullptr;

	bool networkRetry = 0;
	
};


#endif