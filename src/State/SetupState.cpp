#include "SetupState.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../Settings.h"

SetupState* SetupState::instance = nullptr;

SetupState::SetupState(){
	instance = this;
}

SetupState::~SetupState(){
	instance = nullptr;
}

void SetupState::enter(){
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(SampleStore::load(SampleGroup::Generic, "setupMode"));
	Playback.setPlaybackDoneCallback([](){
		LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
	});

	/*Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		if(instance == nullptr) return;
		instance->exit();
	});*/
}

void SetupState::exit(){
	/*Input::getInstance()->removeBtnPressCallback(BTN_PIN);
	Net.connect();*/
}
