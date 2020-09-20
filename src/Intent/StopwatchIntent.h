#ifndef SPENCER_STOPWATCHINTENT_H
#define SPENCER_STOPWATCHINTENT_H
#include <Arduino.h>
#include "Intent.hpp"
class DateTime;
class TimeSpan;
enum StopwatchState{
	waitingState, runningState, finishedState  
};
class StopwatchIntent: public Intent
{
public:
	StopwatchIntent(void* params);
	virtual ~StopwatchIntent() override;
	void loop() override;
private:
	static StopwatchIntent* instance;
	DateTime start;
	StopwatchState state = waitingState;
	TimeSpan timeDiff;
};


#endif