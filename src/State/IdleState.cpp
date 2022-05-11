#include <Input/Input.h>
#include "IdleState.h"
#include <Spencer.h>
#include "ListenState.h"
#include <Spencer.h>
#include "../Services/UpdateChecker.h"
#include <Audio/Playback.h>
#include <Loop/LoopManager.h>
#include <Devices/Matrix/MatrixAnimGIF.h>

IdleState* IdleState::instance = nullptr;

IdleState::IdleState(){
	instance = this;
	for(uint8_t i = 0; i < totalAnimations; i++){
		unusedIdleAnimations.push_back(i);
	}
}

IdleState::~IdleState(){
	instance = nullptr;
}

void IdleState::enter(){
	digitalWrite(LED_PIN, 0);

	LoopManager::addListener(this);

	notifyingUpdate = false;
	if(UpdateChecker.updateAvailable() && !UpdateChecker.hasNotified()){
		UpdateChecker.notify();
		notifyingUpdate = true;

		delete anim;
		anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-talk.gif"));
		LEDmatrix.startAnimation(anim);
		Playback.playMP3(SampleStore::load(Generic, "update"));
		Playback.setPlaybackDoneCallback([](){
			if(instance == nullptr) return;
			instance->startRandomAnimation();
			instance->notifyingUpdate = false;
		});
	}else{
		startRandomAnimation();
	}

	Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		if(instance == nullptr) return;
		digitalWrite(LED_PIN, 1);
		changeState(new ListenState());
	});
}

void IdleState::exit(){
	LoopManager::removeListener(this);
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
	delete anim;
}

void IdleState::loop(uint _micros)
{
	if(notifyingUpdate) return;

	if(anim->getGIF().getLoopCount() > requiredAnimationLoops - 1){
		startRandomAnimation();
	}
}

void IdleState::startRandomAnimation()
{
	uint animationIndex = 0;
	uint randomIndex = random(0, unusedIdleAnimations.size());
	animationIndex = unusedIdleAnimations[randomIndex];
	unusedIdleAnimations.erase(unusedIdleAnimations.begin()+randomIndex);

	usedIdleAnimations.push_back(animationIndex);
	if(usedIdleAnimations.size() == (int(totalAnimations/2) + 1)){
		unusedIdleAnimations.push_back(usedIdleAnimations[0]);
		usedIdleAnimations.erase(usedIdleAnimations.begin());
	}
	char buffer[20];
	if(animationIndex == 0){
		sprintf(buffer, "GIF-yawn.gif", animationIndex);
		requiredAnimationLoops = 1;
	}else if(animationIndex == 11){
		sprintf(buffer, "GIF-wink.gif", animationIndex);
		requiredAnimationLoops = 1;
	}else{
		sprintf(buffer, "GIF-idle%d.gif", animationIndex);
		if(animationIndex == 4){
			requiredAnimationLoops = 1;
		}else{
			requiredAnimationLoops = 3;
		}
	}
	delete anim;
	anim = new MatrixAnimGIF( new SerialFlashFileAdapter(buffer));
	LEDmatrix.startAnimation(anim);
	animationLoopCounter = 0;
}