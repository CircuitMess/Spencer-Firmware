#include <Loop/LoopManager.h>
#include "ListenState.h"
#include "../Services/Audio/Playback.h"
#include "../Speech/SpeechToIntent.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Recording.h"
#include "ProcessState.h"
#include "../Services/LimitTrackingService/LimitTrackingService.h"
#include "../Settings.h"
#include "IdleState.h"
#include "../Services/TimeService/TimeService.h"
ListenState* ListenState::instance = nullptr;

ListenState::ListenState(){
	instance = this;
}

ListenState::~ListenState(){

}

void ListenState::enter(){
	if(LimitTrackingService.getSTTusage() >= 0.98 && LimitTrackingService.getSTTusage() < 0.99 && !Settings.get().limitTrackData.dailyWarning){
		Playback.playMP3(SampleStore::load(SampleGroup::Warnings, "nearLimit"));
		Playback.setPlaybackDoneCallback([](){
			LEDmatrix.startAnimation(new Animation("GIF-listen.gif"), true);
			Recording.addJob({ &instance->recordResult });
			LoopManager::addListener(instance);
		});
		Settings.get().limitTrackData.dailyWarning = 1;
		Settings.get().limitTrackData.dailyWarningTime = TimeService.getTime();
		Settings.store();
	}else if(LimitTrackingService.getSTTusage() >= 0.99){
		if(Settings.get().limitTrackData.allowOverLimit && Settings.get().limitTrackData.dailyWarning){
			Settings.get().limitTrackData.dailyWarning = 1;
			Settings.get().limitTrackData.dailyWarningTime = TimeService.getTime();
			Settings.store();
		}else if(!Settings.get().limitTrackData.allowOverLimit){
			Playback.playMP3(SampleStore::load(SampleGroup::Warnings, "overLimit"));
			Playback.setPlaybackDoneCallback([](){
				changeState(new IdleState());
			});
		}
	}else{
		LEDmatrix.startAnimation(new Animation("GIF-listen.gif"), true);
		Recording.addJob({ &instance->recordResult });
		LoopManager::addListener(instance);
	}
}

void ListenState::exit(){
	LoopManager::removeListener(this);
}

void ListenState::loop(uint micros){
	if(recordResult != nullptr){
		changeState(new ProcessState(recordResult));
	}
}