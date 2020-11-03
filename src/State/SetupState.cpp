#include "SetupState.h"
#include <Input/Input.h>
#include "../../Spencer.hpp"
#include "../LEDmatrix/LEDmatrix.h"
#include "../HTTPserver/HTTPserver.h"
#include "../Services/Audio/Playback.h"
#include <loop/LoopManager.h>
SetupState* SetupState::instance = nullptr;

SetupState::SetupState(){
	instance = this;
}

SetupState::~SetupState(){
	instance = nullptr;
}

void SetupState::enter(){
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(SampleStore::load(SampleGroup::Generic, "startup"));
	Playback.setPlaybackDoneCallback([](){
		LEDmatrix.startAnimation(new Animation("GIF-wifi.gif"), true);
	});
	LoopManager::addListener(this);
}

void SetupState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
}

void SetupState::loop(uint _time)
{
}