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
#include <Devices/Matrix/MatrixAnimGIF.h>

StartupState::StartupState(bool firstTime) : firstTime(firstTime){

}

void StartupState::enter(){
	Playback.playMP3(SampleStore::load(Special, "startup"));

	anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-startup.gif"));
	anim->getGIF().setLoopMode(GIF::SINGLE);
	startupEnd = millis() + anim->getLoopDuration();
	LEDmatrix.startAnimation(anim);

	LoopManager::addListener(this);
}

void StartupState::exit(){
	delete anim;
}

void StartupState::loop(uint micros){
	if(millis() >= startupEnd){
		LoopManager::removeListener(this);

		if(firstTime){
			anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-talk.gif"));
			LEDmatrix.startAnimation(anim);
			Playback.playMP3(SampleStore::load(Generic, "firstStartup"));

			Playback.setPlaybackDoneCallback([](){
				changeState(new SetupState());
			});
		}else{
			anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-wifi.gif"));
			LEDmatrix.startAnimation(anim);

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
