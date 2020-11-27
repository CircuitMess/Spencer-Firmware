#include "StopwatchIntent.h"
#include <Input/Input.h>
#include "../../Spencer.hpp"
#include "../Services/TimeService/TimeService.h"
#include "../Services/Audio/Playback.h"
#include "../LEDmatrix/LEDmatrix.h"
StopwatchIntent* StopwatchIntent::instance = nullptr;
StopwatchIntent::StopwatchIntent()
{
	instance = this;
	state = waitingState;
}
StopwatchIntent::~StopwatchIntent()
{
}
void StopwatchIntent::loop(uint _time)
{
	switch (state)
	{
	case waitingState:
		if(stopTalkingFlag){
			blinkTime+=_time;
			if((blinkTime > 500000 && blinkState) || (blinkTime > 200000 && !blinkState)){
				blinkState = !blinkState;
				blinkTime = 0;
			}
			if(blinkState){
				drawTime(timeDiff.minutes(), timeDiff.seconds());
			}else{
				LEDmatrix.clear();
			}
		}
		break;

	case runningState:
		timeDiff = TimeSpan(TimeService.getTime() - start.unixtime());
		drawTime(timeDiff.minutes(), timeDiff.seconds());
		if(timeDiff.hours() > 0){
			LEDmatrix.clear();
			done();
		}
		break;

	case finishedState:
		blinkTime+=_time;
		if((blinkTime > 500000 && blinkState) || (blinkTime > 200000 && !blinkState))
		{
			blinkState = !blinkState;
			blinkTime = 0;
		}
		if(finishedTime > 3000000){
			LEDmatrix.stopAnimation();
			done();
			return;
		}
		if(!Playback.isRunning()){
			finishedTime+=_time;
		}
		if(blinkState){
			drawTime(timeDiff.minutes(), timeDiff.seconds());
		}else{
			LEDmatrix.clear();
		}
		break;
	}
}
void StopwatchIntent::drawTime(uint minutes, uint seconds)
{
	LEDmatrix.clear();
	if(minutes/10 + '0' != '1'){
		LEDmatrix.drawChar(0,7,minutes/10 + '0', 255, 0);
	}else{
		LEDmatrix.drawChar(1,7,minutes/10 + '0', 255, 0);
	}
	LEDmatrix.drawChar(4,7,(minutes%10) + '0', 255, 0);
	LEDmatrix.drawChar(9,7, seconds/10 + '0', 255, 0);
	if(seconds/10 == 1){
		LEDmatrix.drawChar(12,7,(seconds%10) + '0', 255, 0);
	}else{
		LEDmatrix.drawChar(13,7,(seconds%10) + '0', 255, 0);
	}
}

void StopwatchIntent::enter()
{
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), 1);
	Playback.playMP3(SampleStore::load(SampleGroup::Time, "PressToStart"));
	Playback.setPlaybackDoneCallback([](){
		instance->stopTalkingFlag = 1;
		LEDmatrix.stopAnimation();
	});
	Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
		LEDmatrix.stopAnimation();
		if(Playback.isRunning()){
			Playback.stopPlayback(); //in case spencer is still talking when pressed
		}
		instance->state = runningState;
		instance->start = DateTime((uint32_t)TimeService.getTime());
		Input::getInstance()->setBtnPressCallback(BTN_PIN, [](){
			Input::getInstance()->removeBtnPressCallback(BTN_PIN);
			instance->state = finishedState;
			instance->blinkState = 1;
			instance->blinkTime = 0;

			instance->timeDiff = TimeSpan(TimeService.getTime() - instance->start.unixtime());
			CompositeAudioFileSource* finishedTrack = new CompositeAudioFileSource();
			char buffer[3];
			if(instance->timeDiff.minutes() > 0){
				if(instance->timeDiff.minutes() > 19){
					sprintf(buffer, "%d", (instance->timeDiff.minutes()/10)*10);
					finishedTrack->add(SampleStore::load(Numbers, buffer));
					if(instance->timeDiff.minutes() % 10 > 0){
						sprintf(buffer, "%d", instance->timeDiff.minutes()%10);
						finishedTrack->add(SampleStore::load(Numbers, buffer));
					}
				}
				else{
					sprintf(buffer, "%d", instance->timeDiff.minutes());
					finishedTrack->add(SampleStore::load(Numbers, buffer));
				}
				finishedTrack->add(SampleStore::load(SampleGroup::Time, instance->timeDiff.minutes() > 1 ? "minutes" : "minute"));
				finishedTrack->add(SampleStore::load(SampleGroup::Generic, "and"));
			}

			if(instance->timeDiff.seconds() > 19){
				sprintf(buffer, "%d", (instance->timeDiff.seconds()/10)*10);
				finishedTrack->add(SampleStore::load(Numbers, buffer));
				if(instance->timeDiff.seconds() % 10 > 0){
					sprintf(buffer, "%d", instance->timeDiff.seconds()%10);
					finishedTrack->add(SampleStore::load(Numbers, buffer));
				}
			}
			else if(instance->timeDiff.seconds() > 0){
				sprintf(buffer, "%d", instance->timeDiff.seconds());
				finishedTrack->add(SampleStore::load(Numbers, buffer));
			}

			if(instance->timeDiff.seconds() == 0 && instance->timeDiff.minutes() == 0){
				finishedTrack->add(SampleStore::load(Time, "under"));
				finishedTrack->add(SampleStore::load(Numbers, "1"));
				finishedTrack->add(SampleStore::load(Time, "second"));
			}else{
				finishedTrack->add(SampleStore::load(SampleGroup::Time, instance->timeDiff.seconds() > 1 ? "seconds" : "second"));
			}
			
			finishedTrack->add(SampleStore::load(SampleGroup::Time, "NewRecord"));
			Playback.playMP3(finishedTrack);
		});
	});
}

void StopwatchIntent::exit()
{
	Input::getInstance()->removeBtnPressCallback(BTN_PIN);
}