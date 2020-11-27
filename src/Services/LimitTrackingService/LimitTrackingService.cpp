#include "LimitTrackingService.h"
#include <Loop/LoopManager.h>
#include "../../Settings.h"
#include "../TimeService/TimeService.h"
LimitTrackingServiceImpl LimitTrackingService;

LimitTrackingServiceImpl::LimitTrackingServiceImpl()
{
}

LimitTrackingServiceImpl::~LimitTrackingServiceImpl()
{
}

void LimitTrackingServiceImpl::begin()
{
	LoopManager::addListener(this);
	currentSTTseconds = Settings.get().limitTrackData.STTseconds;
	currentTTSchars = Settings.get().limitTrackData.TTSchars;
	startingTime = Settings.get().limitTrackData.cycleStartTime;
	if(startingTime == 0){
		startingTime = TimeService.getTime();
	}
}

void LimitTrackingServiceImpl::end()
{
	LoopManager::removeListener(this);
}
void LimitTrackingServiceImpl::loop(uint _time)
{
	dailyWarningResetTime += _time;
	if(dailyWarningResetTime >= 3600000000){ //check for new day every hour
		if(DateTime(TimeService.getTime()).day() != DateTime(Settings.get().limitTrackData.dailyWarningTime).day()){
			Settings.get().limitTrackData.dailyWarning = 0; //reset daily warning
			Settings.get().limitTrackData.dailyWarningTime = TimeService.getTime();
			Settings.store();
		}
	}
}
void LimitTrackingServiceImpl::addSTTusage(uint32_t audioLength)
{
	currentSTTseconds += (audioLength / 15) + ((audioLength%15 > 0) ? 15 : 0); //nearest 15 seconds interval
	Settings.get().limitTrackData.STTseconds = currentSTTseconds;
	Settings.store();
}
void LimitTrackingServiceImpl::addTTSusage(uint32_t charactersCount)
{
	currentTTSchars+=charactersCount;
	Settings.get().limitTrackData.TTSchars = currentTTSchars;
	Settings.store();
}

float LimitTrackingServiceImpl::getSTTusage()
{
	return ((float)currentSTTseconds) / ((float)STT_MAX_SECONDS);
}
float LimitTrackingServiceImpl::getTTSusage()
{
	return ((float)currentTTSchars) / ((float)TTS_MAX_CHARS);
}

