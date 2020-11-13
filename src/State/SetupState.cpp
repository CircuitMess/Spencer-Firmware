#include "SetupState.h"
#include <Input/Input.h>
#include "../../Spencer.hpp"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../Net.h"
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
		LEDmatrix.startAnimation(new Animation("GIF-wifi.gif"), true);
	});

	Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		if(instance == nullptr) return;
		instance->exit();
	});

	server.start();
}

void SetupState::exit(){
	server.stop();
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);

	Net.set(Settings.get().SSID, Settings.get().pass);
	Net.connect();
}
