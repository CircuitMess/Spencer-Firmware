#include <Loop/LoopManager.h>
#include "ListenState.h"
#include "../Services/Audio/Playback.h"
#include "../Speech/SpeechToIntent.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Recording.h"
#include "ProcessState.h"

ListenState::ListenState(){

}

ListenState::~ListenState(){

}

void ListenState::enter(){
	Playback.stopPlayback();
	LEDmatrix.startAnimation(new Animation("GIF-listen.gif"), true);
	Recording.addJob({ &recordResult });
	LoopManager::addListener(this);
}

void ListenState::exit(){
	LoopManager::removeListener(this);
}

void ListenState::loop(uint micros){
	if(recordResult != nullptr){
		changeState(new ProcessState(recordResult));
	}
}