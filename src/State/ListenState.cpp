#include "ListenState.h"
#include "../Services/Audio/Audio.h"
#include "../Speech/SpeechToIntent.h"
#include "IdleState.h"
#include "../Speech/TextToSpeech.h"
#include "../Intent/Intent.hpp"
#include "../Intent/IntentStore.h"
#include "IntentState.h"

ListenState::ListenState(){

}

ListenState::~ListenState(){

}

void ListenState::enter(){
	// set listen animation

	audio.record([](){
		SpeechToIntent.identifyVoice([](IntentResult* result){
			const IntentInfo* intent;

			if(result == nullptr || (intent = IntentStore::findIntent(result->intent)) == nullptr){
				audio.playMP3("generic-NO_INTENT.mp3");
				changeState(new IdleState());
				return;
			}

			changeState(new IntentState(intent->launch(nullptr)));
		});
	});
}

void ListenState::exit(){

}
