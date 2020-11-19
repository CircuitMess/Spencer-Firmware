#include <Input/Input.h>
#include "SetupState.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../Settings.h"
#include "../../Spencer.hpp"
#include "../Net.h"

SetupState::SetupState(){

}

SetupState::~SetupState(){

}

void SetupState::enter(){
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(SampleStore::load(SampleGroup::Generic, "setupMode"));
	Playback.setPlaybackDoneCallback([](){
		LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
	});

	Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		Input::getInstance()->removeBtnPressCallback(BTN_PIN);
		Net.connect();
	});
}

void SetupState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
}
