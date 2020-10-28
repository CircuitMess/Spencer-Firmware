#include <Loop/LoopManager.h>
#include "IntentState.h"
#include "IdleState.h"
#include "../Intent/Intent.hpp"

IntentState* IntentState::instance = nullptr;

IntentState::IntentState(Intent* intent, IntentInfo::Upsell* upsell) : intent(intent), upsell(upsell){
	instance = this;
}

IntentState::~IntentState(){
	instance = nullptr;
}

void IntentState::intentDone(){
	State::changeState(new IdleState());
}

void IntentState::loop(uint micros){
	intent->loop(micros);
}

void IntentState::enter(){
	LoopManager::addListener(this);
}

void IntentState::exit(){
	LoopManager::removeListener(this);
}
