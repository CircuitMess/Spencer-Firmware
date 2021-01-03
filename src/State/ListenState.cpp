#include <Loop/LoopManager.h>
#include "ListenState.h"
#include <Audio/Playback.h>
#include <Speech/SpeechToIntent.h>
#include <Spencer.h>
#include <Audio/Recording.h>
#include "ProcessState.h"

ListenState::ListenState(){

}

ListenState::~ListenState(){

}

void ListenState::enter(){
	Playback.stopPlayback();
	LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-listen.gif")), true);
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