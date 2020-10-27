#include <Loop/LoopManager.h>
#include "IntentState.h"

IntentState::IntentState(Intent* intent) : intent(intent){

}

void IntentState::loop(uint micros){
	intent->loop();
}

void IntentState::enter(){
	LoopManager::addListener(this);
}

void IntentState::exit(){
	LoopManager::removeListener(this);
}
