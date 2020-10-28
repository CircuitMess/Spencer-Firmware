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
	LEDmatrix.startAnimation(new Animation("GIF-listen.gif"), true);
	LEDmatrix.push();

	Audio.record([](){
		LEDmatrix.startAnimation(new Animation("GIF-loading1.gif"), true);
		LEDmatrix.push();

		SpeechToIntent.identifyVoice([](IntentResult* result){
			const IntentInfo* intent;

			if(result == nullptr || (intent = IntentStore::findIntent(result->intent)) == nullptr){
				LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
				Audio.playMP3("generic-NO_INTENT.mp3");
				changeState(new IdleState());
				return;
			}

			changeState(new IntentState(intent->launch(nullptr)));
		});
	});
}

void ListenState::exit(){

}
