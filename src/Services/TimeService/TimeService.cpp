#include "TimeService.h"
#include <NTPClient.h>
#include <WiFi.h>
#include "../LocationService/LocationService.h"
TimeServiceImpl TimeService;
void TimeServiceImpl::setTime(uint unixTime)
{
	unixtime = unixTime;
	currentMillis = millis();
}
uint TimeServiceImpl::getTime()
{
	uint diff = (millis() - currentMillis) / 1000;
	return (unixtime + LocationService.getLocation()->timezoneOffset + diff);
}
bool TimeServiceImpl::fetchTime()
{
	ntpUDP = new WiFiUDP();
	timeClient = new NTPClient(*ntpUDP);
	timeClient->begin();
	
	if(!timeClient->forceUpdate())
	{
		Serial.println("fetch failed");
		return false;
	}
	setTime(timeClient->getEpochTime());
	srand(timeClient->getEpochTime());

	timeClient->end();
	ntpUDP->stop();
	delete timeClient;
	delete ntpUDP;

	return true;
}
void TimeServiceImpl::loop(uint _time)
{
	if(!WiFi.status() == WL_CONNECTED) return;

	refreshMicros+=_time;
	if(refreshMicros > 300000000)
	{
		fetchTime();
		refreshMicros = 0;
	}
}
