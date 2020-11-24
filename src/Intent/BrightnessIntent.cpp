#include "BrightnessIntent.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
BrightnessIntent::BrightnessIntent(void* _params)
{
	for(uint8_t i = 0; i < 3; i++){
		if(LEDmatrix.getBrightness() == brightnessLevelValues[i]){
			startingLevel = i;
			break;
		}
	}
	param = (const char*)(_params);
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
	LEDmatrix.setBrightness(brightnessLevelValues[brightnessLevel]);
	CompositeAudioFileSource* output = new CompositeAudioFileSource();
	output->add(SampleStore::load(SampleGroup::Brightness, "setTo"));
	output->add(SampleStore::load(SampleGroup::Levels, brightnessLevelNames[brightnessLevel]));
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(output);
	Playback.setPlaybackDoneCallback([](){
		done();
	});
}

BrightnessIntent::~BrightnessIntent()
{
	
}

void BrightnessIntent::loop(uint _time)
{
}