#include <Loop/LoopManager.h>
#include "ListenState.h"
#include "../Services/Audio/Playback.h"
#include "../Speech/SpeechToIntent.h"
#include "IdleState.h"
#include "../Intent/Intent.hpp"
#include "../Intent/IntentStore.h"
#include "IntentState.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Recording.h"

ListenState::ListenState(){

}

ListenState::~ListenState(){

}

void ListenState::enter(){
	LEDmatrix.startAnimation(new Animation("GIF-listen.gif"), true);
	Recording.addJob({ &recordResult });
	LoopManager::addListener(this);
}

void ListenState::exit(){
	LoopManager::removeListener(this);
	delete intentResult;
}

void ListenState::processRecording(){
	LEDmatrix.startAnimation(new Animation("GIF-loading1.gif"), true);
	SpeechToIntent.addJob({ recordResult, &intentResult });
}

void ListenState::processIntent(){
	const IntentInfo* intent;
	if((intent = IntentStore::findIntent(intentResult->intent)) == nullptr){
		LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
		Playback.playMP3("generic-NO_INTENT.mp3");
		changeState(new IdleState());
		return;
	}

	changeState(new IntentState(intent->launch(std::map<std::string, std::string>{}), intent->upsell));
}

void ListenState::loop(uint micros){
	if(recordResult != nullptr){
		processRecording();
		recordResult = nullptr;
		return;
	}

	if(intentResult != nullptr){
		processIntent();
	}
}
