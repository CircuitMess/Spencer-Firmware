#include "TimeService.h"
TimeServiceImpl TimeService;
void TimeServiceImpl::setTime(uint unixTime)
{
	unixtime = unixTime;
}
uint TimeServiceImpl::getTime()
{
	uint diff = millis() - currentMillis;
	unixtime+=diff;
	currentMillis+=diff;
	return unixtime;
}