#include "ErrorState.h"
#include "../Services/Audio/Playback.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "IdleState.h"
#include "SetupState.h"

ErrorState::ErrorState(ErrorType type) : type(type){ }

void ErrorState::enter(){
	switch(type){
		case WIFI:
			doWifi();
			break;
	}
}

void ErrorState::exit(){

}

void ErrorState::doWifi(){
	LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
	Playback.playMP3(SampleStore::load(Generic, "noNet"));

	Playback.setPlaybackDoneCallback([](){
		changeState(new SetupState());
	});
}
