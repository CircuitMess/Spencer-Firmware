#include <Loop/LoopManager.h>
#include "ProcessState.h"
#include "../Intent/IntentInfo.hpp"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../Intent/IntentStore.h"
#include "IdleState.h"
#include "ErrorState.h"
#include "SetupState.h"

ProcessState::ProcessState(const char* recordingFilename) : recordingFilename(recordingFilename){

}

void ProcessState::processIntent(){
	const IntentInfo* intent;

	bool settings;

	if(intentResult->error == IntentResult::OFFLINE){
		delete intentResult;
		intentResult = nullptr;

		LoopManager::removeListener(this);
		State::changeState(new ErrorState(ErrorType::WIFI));
		return;
	}else if(intentResult->error == IntentResult::NETWORK){
		delete intentResult;
		intentResult = nullptr;

		if(retried){
			LoopManager::removeListener(this);
			State::changeState(new ErrorState(ErrorType::WIFI));
			return;
		}

		retried = true;
		SpeechToIntent.addJob({ recordingFilename, &intentResult });
		return;
	}else if(intentResult->error == IntentResult::INTENT
			|| intentResult->error == IntentResult::JSON
			|| intentResult->intent == nullptr
			|| (!(settings = std::string(intentResult->intent) == "settings") && (intent = IntentStore::findIntent(intentResult->intent)) == nullptr)){
		if(intentResult->error == IntentResult::JSON){
			LEDmatrix.startAnimation(new Animation("GIF-error500.gif"), true);
			Playback.playMP3("generic-mess.mp3");
		}else{
			LEDmatrix.startAnimation(new Animation("GIF-questionMark.gif"), true);
			Playback.playMP3("generic-NO_INTENT.mp3");
		}

		delete intentResult;
		intentResult = nullptr;

		Playback.setPlaybackDoneCallback([](){
			changeState(new IdleState());
		});

		return;
	}

	if(settings){
		changeState(new SetupState());
		return;
	}

	changeState(new IntentState(intent->launch(std::map<std::string, std::string>{}), intent->upsell));
}

void ProcessState::bleep(){
	if(random(0,2)) return;

	uint8_t index =  random(0, 12);
	char randomSound[18];
	sprintf(randomSound, "randomNoise%d", index);
	// Playback.setVolume(Playback.getVolume()/2);
	Playback.playMP3(SampleStore::load(SampleGroup::Special, randomSound));
	sprintf(randomSound, "GIF-random%d.gif", index);
	LEDmatrix.startAnimation(new Animation(randomSound), true);
}

void ProcessState::enter(){
	uint8_t loadingAnimationIndex =  random(0, 8);
	char randomAnimation[20];
	sprintf(randomAnimation, "GIF-loading%d.gif", loadingAnimationIndex);
	LEDmatrix.startAnimation(new Animation(randomAnimation), true);
	SpeechToIntent.addJob({ recordingFilename, &intentResult });
	LoopManager::addListener(this);
	bleep();
}

void ProcessState::exit(){
	LoopManager::removeListener(this);
	delete intentResult;
}

void ProcessState::loop(uint micros){
	if(intentResult != nullptr){
		processIntent();
	}
}
