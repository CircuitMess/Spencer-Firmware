#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include "SetupState.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../../Spencer.hpp"
#include "../Net.h"
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

	static auto doConnect = [](){
		LEDmatrix.startAnimation(new Animation("GIF-wifi.gif"), true);

		Net.connect([](wl_status_t status){
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
