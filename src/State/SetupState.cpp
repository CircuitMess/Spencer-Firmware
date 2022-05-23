#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include "SetupState.h"
#include <Spencer.h>
#include <Audio/Playback.h>
#include <Spencer.h>
#include <Network/Net.h>
#include "IdleState.h"
#include "../Services/LocationService/LocationService.h"
#include "../Services/TimeService/TimeService.h"
#include <Devices/Matrix/MatrixAnimGIF.h>

MatrixAnimGIF* SetupState::anim = nullptr;
SetupState::SetupState(){

}

SetupState::~SetupState(){

}

void SetupState::enter(){
	setup.start();

	anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-talk.gif"));
	LEDmatrix.startAnimation(anim);
	Playback.playMP3(SampleStore::load(SampleGroup::Generic, "setupMode"));
	Playback.setPlaybackDoneCallback([](){
		SetupState::anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-noWifi.gif"));
		LEDmatrix.startAnimation(SetupState::anim);
	});


	static bool connecting = false;
	static auto doConnect = [](){
		if(connecting) return;
		connecting = true;

		Playback.stopPlayback(false);
		SetupState::anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-wifi.gif"));
		LEDmatrix.startAnimation(SetupState::anim);

		Net.connect([](wl_status_t status){
			connecting = false;

			if(status == WL_CONNECTED){
				LocationService.fetchLocation();
				TimeService.fetchTime();
				changeState(new IdleState());
			}else{
				SetupState::anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-noWifi.gif"));
				LEDmatrix.startAnimation(SetupState::anim);
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
	delete anim;
}
