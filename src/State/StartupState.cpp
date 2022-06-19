#include <Loop/LoopManager.h>
#include "StartupState.h"
#include <Spencer.h>
#include <Settings.h>
#include "IdleState.h"
#include "ErrorState.h"
#include "../Services/LocationService/LocationService.h"
#include "../Services/TimeService/TimeService.h"
#include <Audio/Playback.h>
#include "SetupState.h"

StartupState::StartupState(bool firstTime) : firstTime(firstTime){

}

void StartupState::enter(){
	Playback.playMP3(SampleStore::load(Special, "startup"));
	Animation* startupAnim = new Animation( new SerialFlashFileAdapter("GIF-startup.gif"));

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
			LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-talk.gif")), true);
			Playback.playMP3(SampleStore::load(Generic, "firstStartup"));

			Playback.setPlaybackDoneCallback([](){
				changeState(new SetupState());
			});
		}else{
			LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-wifi.gif")), true);

			Net.connect([](wl_status_t status){
				if(status == WL_CONNECTED){
					LocationService.fetchLocation();
					TimeService.fetchTime();
					changeState(new IdleState());
				}else{
					changeState(new ErrorState(ErrorType::WIFI));
				}
			});
		}
	}
}
