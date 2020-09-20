#include "StopwatchIntent.h"
#include <Input/InputGPIO.h>
#include "../../Spencer.hpp"
#include "../Services/TimeService/TimeService.h"
StopwatchIntent* StopwatchIntent::instance = nullptr;
StopwatchIntent::StopwatchIntent(void* params) : Intent(params)
{
	//"press my head to start", begin waiting animation
	InputGPIO::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		instance->state = runningState;
		instance->start = DateTime(timeService.getTime());
		InputGPIO::getInstance()->setBtnPressCallback(BTN_PIN, [](){
			instance->state = finishedState;
			instance->timeDiff = timeService.getTime() - instance->start;
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
		timeDiff = timeService.getTime() - start;
		//print timeDiff
		break;
	case finishedState:
		//print timeDiff
		break;
	}
}

