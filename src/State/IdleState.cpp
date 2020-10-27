#include <Input/Input.h>
#include "IdleState.h"
#include "../../Spencer.hpp"
#include "ListenState.h"
#include "../LEDmatrix/LEDmatrix.h"

IdleState* IdleState::instance = nullptr;

IdleState::IdleState(){
	instance = this;
}

IdleState::~IdleState(){
	instance = nullptr;
}

void IdleState::enter(){
	// set idle animation

	Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		if(instance == nullptr) return;

		changeState(new ListenState());
	});
}

void IdleState::exit(){
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
}
