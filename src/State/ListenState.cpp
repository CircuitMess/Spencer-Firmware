#include <Loop/LoopManager.h>
#include "ListenState.h"
#include "../Services/Audio/Audio.h"
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
	LEDmatrix.push();

	Recording.record([](){ });

	LEDmatrix.startAnimation(new Animation("GIF-loading1.gif"), true);

	SpeechToIntent.addJob({ "recording.wav", &intentResult });
	LoopManager::addListener(this);
}

void ListenState::exit(){

}

void ListenState::loop(uint micros){
	if(intentResult == nullptr) return;
	LoopManager::removeListener(this);

	const IntentInfo* intent;
	if((intent = IntentStore::findIntent(intentResult->intent)) == nullptr){
		delete intentResult;
		intentResult = nullptr;

		LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
		Audio.playMP3("generic-NO_INTENT.mp3");
		changeState(new IdleState());
		return;
	}

	delete intentResult;
	intentResult = nullptr;

	changeState(new IntentState(intent->launch(nullptr), intent->upsell));
}
