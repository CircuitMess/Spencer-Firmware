#ifndef SPENCER_TIMESERVICE_H
#define SPENCER_TIMESERVICE_H

#include "DateTime.hpp"
class WiFiUDP;
class NTPClient;
class TimeServiceImpl
{
public:
	uint getTime();
	void setTime(uint unixTime);
	bool fetchTime();
private:
	uint unixtime = 0;
	uint currentMillis = millis();
	WiFiUDP *ntpUDP;
	// By default 'pool.ntp.org' is used with 60 seconds update interval and
	// no offset
	NTPClient *timeClient;
};
extern TimeServiceImpl TimeService;

#endif