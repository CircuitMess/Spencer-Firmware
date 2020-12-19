#ifndef SPENCER_TIMESERVICE_H
#define SPENCER_TIMESERVICE_H

#include <Net/Net.h>
#include "DateTime.hpp"
#include <Loop/LoopListener.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

class WiFiUDP;
class NTPClient;
class Task;

class TimeServiceImpl : public LoopListener, public NetStateListener
{
public:
	TimeServiceImpl();

	/**
	 * Starts the time service. This immediately fetches the current time.
	 */
	void begin();
	void end();

	uint getTime();
	void setTime(uint unixTime);

	void fetchTime();
	void loop(uint _time) override;

private:
	uint unixtime = 0;
	uint currentMillis = millis();
	WiFiUDP ntpUDP;
	// By default 'pool.ntp.org' is used with 60 seconds update interval and
	// no offset
	NTPClient timeClient;
	uint refreshMicros = 0;

	bool running = false;
	bool fetching = false;

	Task* fetchTask = nullptr;

	void state(wl_status_t status) override;
};

extern TimeServiceImpl TimeService;

#endif