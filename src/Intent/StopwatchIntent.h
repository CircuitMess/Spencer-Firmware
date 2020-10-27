#ifndef SPENCER_STOPWATCHINTENT_H
#define SPENCER_STOPWATCHINTENT_H

#include <Arduino.h>
#include "Intent.hpp"
#include "../Services/TimeService/DateTime.hpp"

enum StopwatchState{
	waitingState, runningState, finishedState  
};

class StopwatchIntent: public Intent
{
public:
	StopwatchIntent();
	virtual ~StopwatchIntent() override;
	void loop(uint) override;
private:
	static StopwatchIntent* instance;
	DateTime start;
	StopwatchState state = waitingState;
	TimeSpan timeDiff;
};


#endif