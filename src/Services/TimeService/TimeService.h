#ifndef SPENCER_TIMESERVICE_H
#define SPENCER_TIMESERVICE_H

#include "DateTime.hpp"
class TimeServiceImpl
{
public:
	uint getTime();
	void setTime(uint unixTime);

private:
	uint unixtime = 0;
	uint currentMillis = 0;
};
extern TimeServiceImpl TimeService;

#endif