#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include "SetupState.h"
#include <LEDmatrix/LEDmatrix.h>
#include <Audio/Playback.h>
#include <Spencer.h>
#include <Net/Net.h>
#include "IdleState.h"
#include "../Services/LocationService/LocationService.h"
#include "../Services/TimeService/TimeService.h"

SetupState::SetupState(){

}

SetupState::~SetupState(){

}

void SetupState::enter(){
	setup.start();

	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(SampleStore::load(SampleGroup::Generic, "setupMode"));
	Playback.setPlaybackDoneCallback([](){
		LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
	});


	static bool connecting = false;
	static auto doConnect = [](){
		if(connecting) return;
		connecting = true;

		Playback.stopPlayback(false);
		LEDmatrix.startAnimation(new Animation("GIF-wifi.gif"), true);

		Net.connect([](wl_status_t status){
			connecting = false;

			if(status == WL_CONNECTED){
				LocationService.fetchLocation();
				TimeService.fetchTime();
				changeState(new IdleState());
			}else{
				LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
			}
		});
	};

	Input::getInstance()->setBtnPressCallback(BTN_PIN, doConnect);
	setup.setSettingsSetCallback(doConnect);
}

void SetupState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
	setup.setSettingsSetCallback(nullptr);
	setup.stop();
}
