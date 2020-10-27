#include "StopwatchIntent.h"
#include <Input/InputGPIO.h>
#include "../../Spencer.hpp"
#include "../Services/TimeService/TimeService.h"
StopwatchIntent* StopwatchIntent::instance = nullptr;
StopwatchIntent::StopwatchIntent()
{
	//"press my head to start", begin waiting animation
	InputGPIO::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		instance->state = runningState;
		instance->start = DateTime(timeService.getTime());
		InputGPIO::getInstance()->setBtnPressCallback(BTN_PIN, [](){
			instance->state = finishedState;
			instance->timeDiff = TimeSpan(timeService.getTime() - instance->start.unixtime());
			//say timeDiff
		});
	});
}
StopwatchIntent::~StopwatchIntent()
{
	
}
void StopwatchIntent::loop()
{
	switch (state)
	{
	case waitingState:
		//wait animation, 
		break;
	case runningState:
		timeDiff = TimeSpan(timeService.getTime() - start.unixtime());
		//print timeDiff
		break;
	case finishedState:
		//print timeDiff
		break;
	}
}

