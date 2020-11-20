#include <Input/Input.h>
#include "IdleState.h"
#include "../../Spencer.hpp"
#include "ListenState.h"
#include "../LEDmatrix/LEDmatrix.h"
#include <Loop/LoopManager.h>
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
	LoopManager::addListener(this);
	startRandomAnimation();

	Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		if(instance == nullptr) return;

		changeState(new ListenState());
	});
}

void IdleState::exit(){
	LoopManager::removeListener(this);
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
}

void IdleState::loop(uint _micros)
{
	if(LEDmatrix.getAnimationCompletionRate() >= 99.0 && !animationLoopDone){
		animationLoopCounter++;
		animationLoopDone = true;
		if(animationLoopCounter > 2){
			startRandomAnimation();
		}
	}
	if(LEDmatrix.getAnimationCompletionRate() <= 1){
		animationLoopDone = false;
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
	char buffer[15];
	if(animationIndex == 0){
		sprintf(buffer, "GIF-yawn.gif", animationIndex);
	}else{
		sprintf(buffer, "GIF-idle%d.gif", animationIndex);
	}
	LEDmatrix.startAnimation(new Animation(buffer), true);
	animationLoopCounter = 0;
}