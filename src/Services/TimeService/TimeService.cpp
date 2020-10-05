#include "TimeService.h"
void TimeService::setTime(uint unixTime)
{
	unixtime = unixTime;
}
uint TimeService::getTime()
{
	uint diff = millis() - currentMillis;
	unixtime+=diff;
	currentMillis+=diff;
	return unixtime;
}