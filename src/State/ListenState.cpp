#include <Loop/LoopManager.h>
#include "ListenState.h"
#include <Audio/Playback.h>
#include <Speech/SpeechToIntent.h>
#include <Spencer.h>
#include <Audio/Recording.h>
#include "ProcessState.h"
#include <Devices/Matrix/MatrixAnimGIF.h>

ListenState::ListenState(){

}

ListenState::~ListenState(){

}

void ListenState::enter(){
	Playback.stopPlayback();
	anim = new MatrixAnimGIF(new SerialFlashFileAdapter("GIF-listen.gif"));
	LEDmatrix.startAnimation(anim);
	Recording.addJob({ &recordResult });
	LoopManager::addListener(this);
}

void ListenState::exit(){
	LoopManager::removeListener(this);
	delete anim;
}

void ListenState::loop(uint micros){
	if(recordResult != nullptr){
		changeState(new ProcessState(recordResult));
	}
}