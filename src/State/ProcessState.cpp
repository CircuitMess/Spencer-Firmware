#include <Loop/LoopManager.h>
#include "ProcessState.h"
#include "../Intent/IntentInfo.hpp"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "SetupState.h"
#include "../Intent/IntentStore.h"
#include "IdleState.h"

ProcessState::ProcessState(const char* recordingFilename) : recordingFilename(recordingFilename){

}

void ProcessState::processIntent(){
	const IntentInfo* intent;

	if(intentResult->error == IntentResult::OFFLINE){
		delete intentResult;
		intentResult = nullptr;

		LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
		Playback.playMP3(SampleStore::load(Generic, "noNet"));
		Playback.setPlaybackDoneCallback([](){
			State::changeState(new SetupState());
		});

		LoopManager::removeListener(this);
		return;
	}else if(intentResult->error == IntentResult::NETWORK){
		delete intentResult;
		intentResult = nullptr;

		if(retried){
			LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
			Playback.playMP3(SampleStore::load(Generic, "noNet"));
			Playback.setPlaybackDoneCallback([](){
				State::changeState(new SetupState());
			});

			LoopManager::removeListener(this);
			return;
		}

		retried = true;
		SpeechToIntent.addJob({ recordingFilename, &intentResult });
		return;
	}else if(intentResult->error == IntentResult::INTENT || intentResult->error == IntentResult::JSON || (intent = IntentStore::findIntent(intentResult->intent)) == nullptr){
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

	changeState(new IntentState(intent->launch(std::map<std::string, std::string>{}), intent->upsell));
}

void ProcessState::bleep(){
	if(random(0,2)) return;

	char randomSound[15];
	sprintf(randomSound, "randomNoise%d", random(0, 12));
	// Playback.setVolume(Playback.getVolume()/2);
	Playback.playMP3(SampleStore::load(SampleGroup::Special, randomSound));
}

void ProcessState::enter(){
	LEDmatrix.startAnimation(new Animation("GIF-loading1.gif"), true);
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