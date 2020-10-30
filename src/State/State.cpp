#include "State.h"

State* State::currentState = nullptr;

void State::changeState(State* state){
	if(currentState != nullptr){
		currentState->exit();
		delete currentState;
	}

	currentState = state;
	state->enter();
}
