#include "SetupState.h"
#include <Input/Input.h>
#include "../../Spencer.hpp"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include <Loop/LoopManager.h>
#include <Input/InputGPIO.h>
#include "../State/IdleState.h"

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

	InputGPIO::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		changeState(new IdleState());
	});
}

void SetupState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
}
