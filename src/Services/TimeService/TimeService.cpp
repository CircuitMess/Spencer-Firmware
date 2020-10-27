#include "TimeService.h"
#include <NTPClient.h>
#include <WiFi.h>

TimeServiceImpl TimeService;
void TimeServiceImpl::setTime(uint unixTime)
{
	unixtime = unixTime;
	currentMillis = millis();
}
uint TimeServiceImpl::getTime()
{
	uint diff = (millis() - currentMillis) / 1000;
	unixtime+=diff;
	return unixtime;
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
	unixtime = timeClient->getEpochTime();
	currentMillis = millis();
	timeClient->end();
	ntpUDP->stop();
	return true;
}