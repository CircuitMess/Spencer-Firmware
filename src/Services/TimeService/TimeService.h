#ifndef SPENCER_TIMESERVICE_H
#define SPENCER_TIMESERVICE_H

#include "DateTime.hpp"
#include <Loop/LoopListener.h>

class WiFiUDP;
class NTPClient;
class TimeServiceImpl : public LoopListener
{
public:
	uint getTime();
	void setTime(uint unixTime);
	bool fetchTime();
	void loop(uint _time) override;

private:
	uint unixtime = 0;
	uint currentMillis = millis();
	WiFiUDP *ntpUDP;
	// By default 'pool.ntp.org' is used with 60 seconds update interval and
	// no offset
	NTPClient *timeClient;
	uint refreshMicros = 0;
};
extern TimeServiceImpl TimeService;

#endif