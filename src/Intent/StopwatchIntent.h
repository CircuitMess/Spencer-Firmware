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
	void loop(uint _time) override;
	void enter() override;
	void exit() override;
	
private:
	static StopwatchIntent* instance;
	DateTime start;
	StopwatchState state = waitingState;
	TimeSpan timeDiff;
	bool stopTalkingFlag = 0;
	uint finishedTime = 0;
	uint blinkTime = 0;
	bool blinkState = 0;

	void drawTime(uint minutes, uint seconds);
};


#endif