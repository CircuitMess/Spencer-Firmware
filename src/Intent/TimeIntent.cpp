#include "TimeIntent.h"
#include "../Services/TimeService/TimeService.h"

TimeIntent::TimeIntent(void* params) : Intent(params)
{
	//start loading animation
	//make prepared statement

	DateTime now = DateTime(static_cast<uint>(params));
	Serial.printf("%d:%d:%d\n", now.hour(), now.minute(), now.second());

}

TimeIntent::~TimeIntent()
{
}
