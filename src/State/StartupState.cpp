#include <Loop/LoopManager.h>
#include "StartupState.h"
#include <LEDmatrix/LEDmatrix.h>
#include <Settings.h>
#include "IdleState.h"
#include "ErrorState.h"
#include "../Services/LocationService/LocationService.h"
#include "../Services/TimeService/TimeService.h"
#include <Audio/Playback.h>
#include "SetupState.h"

StartupState::StartupState(bool firstTime) : firstTime(firstTime){
	if(firstTime){
		Settings.reset();
		Settings.get().brightnessLevel = Settings.get().volumeLevel = 1;
		Settings.store();
	}

	uint8_t brightnessLevelValues[3] = {5, 20, 100};
	float audioLevelValues[3] = {0.1, 0.4, 1.0};
	LEDmatrix.setBrightness(brightnessLevelValues[Settings.get().brightnessLevel]);
	Playback.setVolume(audioLevelValues[Settings.get().volumeLevel]);
}

void StartupState::enter(){
	Playback.playMP3(SampleStore::load(Special, "startup"));
	Animation* startupAnim = new Animation("GIF-startup.gif");

	startupEnd = millis() + startupAnim->getLoopDuration();
	LEDmatrix.startAnimation(startupAnim, false);

	LoopManager::addListener(this);
}

void StartupState::exit(){

}

void StartupState::loop(uint micros){
	if(millis() >= startupEnd){
		LoopManager::removeListener(this);

		if(firstTime){
			LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
			Playback.playMP3(SampleStore::load(Generic, "firstStartup"));

			Playback.setPlaybackDoneCallback([](){
				changeState(new SetupState());
			});
		}else{
			LEDmatrix.startAnimation(new Animation("GIF-wifi.gif"), true);

			Net.connect([](wl_status_t status){
				if(status == WL_CONNECTED){
					LocationService.fetchLocation();
					TimeService.fetchTime();
					State::changeState(new IdleState());
				}else{
					changeState(new ErrorState(ErrorType::WIFI));
				}
			});
		}
	}
}
