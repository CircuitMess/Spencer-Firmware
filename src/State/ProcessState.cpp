#include <Loop/LoopManager.h>
#include "ProcessState.h"
#include "../Intent/IntentInfo.hpp"
#include <Spencer.h>
#include <Audio/Playback.h>
#include "../Intent/IntentStore.h"
#include "IdleState.h"
#include "ErrorState.h"
#include "SetupState.h"
#include <Devices/Matrix/MatrixAnimGIF.h>

ProcessState::ProcessState(const char* recordingFilename) : recordingFilename(recordingFilename){

}

void ProcessState::processIntent(){
	const IntentInfo* intent;

	bool settings;

	if(intentResult->error == IntentResult::NETWORK){
		delete intentResult;
		intentResult = nullptr;

		if(retried){
			LoopManager::removeListener(this);
			State::changeState(new ErrorState(ErrorType::NETWORK));
			return;
		}

		retried = true;
		SpeechToIntent.addJob({ recordingFilename, &intentResult });
		return;
	}else if(intentResult->error == IntentResult::KEY){
		delete intentResult;
		intentResult = nullptr;

		changeState(new ErrorState(ErrorType::APIKEY));
		return;
	}else if(intentResult->error == IntentResult::JSON){
		delete intentResult;
		intentResult = nullptr;

		changeState(new ErrorState(ErrorType::JSON));
	}else if(intentResult->error == IntentResult::INTENT || intentResult->intent == nullptr
			|| (!(settings = (std::string(intentResult->intent) == "Settings")) && (intent = IntentStore::findIntent(intentResult->intent)) == nullptr)){

		delete intentResult;
		intentResult = nullptr;

		delete anim;
		anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-questionMark.gif"));
		LEDmatrix.startAnimation(anim);

		Playback.playMP3(SampleStore::load(Error, "noIntent"));

		Playback.setPlaybackDoneCallback([](){
			changeState(new IdleState());
		});

		return;
	}

	if(settings){
		delete intentResult;
		intentResult = nullptr;

		delete anim;
		anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-talk.gif"));
		LEDmatrix.startAnimation(anim);

		Playback.playMP3(SampleStore::load(Generic, "setupModeEntering"));

		Playback.setPlaybackDoneCallback([](){
			Serial.println("set");
			changeState(new SetupState());
		});

		return;
	}

	changeState(new IntentState(intent->launch(intentResult->entities), intent->upsell));
}

void ProcessState::bleep(){
	if(random(0,2)) return;

	uint8_t index =  random(0, 12);
	char randomSound[18];
	sprintf(randomSound, "randomNoise%d", index);
	Playback.playMP3(SampleStore::load(SampleGroup::Special, randomSound));
	sprintf(randomSound, "GIF-random%d.gif", index);

	delete anim;
	anim = new MatrixAnimGIF( new SerialFlashFileAdapter(randomSound));
	LEDmatrix.startAnimation(anim);
}


void ProcessState::enter(){
	uint8_t loadingAnimationIndex =  random(0, 8);
	char randomAnimation[20];
	sprintf(randomAnimation, "GIF-loading%d.gif", loadingAnimationIndex);

	anim = new MatrixAnimGIF( new SerialFlashFileAdapter(randomAnimation));
	LEDmatrix.startAnimation(anim);

	SpeechToIntent.addJob({ recordingFilename, &intentResult });
	LoopManager::addListener(this);
	bleep();
}

void ProcessState::exit(){
	LoopManager::removeListener(this);
	delete intentResult;
	delete anim;
}

void ProcessState::loop(uint micros){
	if(intentResult != nullptr){
		processIntent();
	}
}
