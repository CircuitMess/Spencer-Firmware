#include "BrightnessIntent.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../Settings.h"
BrightnessIntent::BrightnessIntent(void* _params)
{
	startingLevel = Settings.get().brightnessLevel;
	param = (const char*)(_params);
}

BrightnessIntent::~BrightnessIntent()
{
	
}

void BrightnessIntent::loop(uint _time)
{
}

void BrightnessIntent::enter()
{
	CompositeAudioFileSource* output = new CompositeAudioFileSource();
	if(param == nullptr){
		output->add(SampleStore::load(SampleGroup::Volume, "unknown"));
		output->add(SampleStore::load(SampleGroup::Levels, "low"));
		output->add(SampleStore::load(SampleGroup::Levels, "medium"));
		output->add(SampleStore::load(SampleGroup::Generic, "and"));
		output->add(SampleStore::load(SampleGroup::Levels, "high"));
		output->add(SampleStore::load(SampleGroup::Brightness, "trySaying"));
	}else{
		if(strcmp(param, "low") == 0 || strcmp(param, "min") == 0 || strcmp(param, "minimum") == 0){
			brightnessLevel = 0;
		}else if(strcmp(param, "medium") == 0){
			brightnessLevel = 1;
		}else if(strcmp(param, "high") == 0 || strcmp(param, "max") == 0 || strcmp(param, "maximum") == 0){
			brightnessLevel = 2;
		}else if(strcmp(param, "down") == 0 || strcmp(param, "decrease") == 0){
			brightnessLevel = _max(0, startingLevel - 1);
		}else if(strcmp(param, "up") == 0 || strcmp(param, "increase") == 0){
			brightnessLevel = _min(2, startingLevel + 1);
		}
		Settings.get().brightnessLevel = brightnessLevel;
		Settings.store();
		LEDmatrix.setBrightness(brightnessLevelValues[brightnessLevel]);
		output->add(SampleStore::load(SampleGroup::Brightness, "setTo"));
		output->add(SampleStore::load(SampleGroup::Levels, brightnessLevelNames[brightnessLevel]));
	}
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(output);
	Playback.setPlaybackDoneCallback([](){
		done();
	});
}

void BrightnessIntent::exit()
{
	
}