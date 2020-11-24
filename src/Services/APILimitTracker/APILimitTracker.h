#ifndef SPENCER_APILimitTracker_H
#define SPENCER_APILimitTracker_H

#include "../../Net.h"
#include <Loop/LoopListener.h>

class Task;

class APILimitTrackerImpl : public LoopListener, public NetStateListener
{
public:
	APILimitTrackerImpl();

	void begin();
	void end();

private:
	uint unixtime = 0;
	uint currentMillis = millis();
	void state(wl_status_t status) override;
};

extern APILimitTrackerImpl APILimitTracker;

#endif