#include "VolumeIntent.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../Settings.h"
VolumeIntent::VolumeIntent(void* _params)
{
	startingLevel = Settings.get().volumeLevel;
	
	param = (const char*)(_params);
	CompositeAudioFileSource* output = new CompositeAudioFileSource();
	if(param == nullptr){
		output->add(SampleStore::load(SampleGroup::Volume, "unknown"));
		output->add(SampleStore::load(SampleGroup::Levels, "low"));
		output->add(SampleStore::load(SampleGroup::Levels, "medium"));
		output->add(SampleStore::load(SampleGroup::Generic, "and"));
		output->add(SampleStore::load(SampleGroup::Levels, "high"));
		output->add(SampleStore::load(SampleGroup::Volume, "trySaying"));
	}else{
		if(strcmp(param, "low") == 0 || strcmp(param, "min") == 0 || strcmp(param, "minimum") == 0){
			audioLevel = 0;
		}else if(strcmp(param, "medium") == 0){
			audioLevel = 1;
		}else if(strcmp(param, "high") == 0 || strcmp(param, "max") == 0 || strcmp(param, "maximum") == 0){
			audioLevel = 2;
		}else if(strcmp(param, "down") == 0 || strcmp(param, "decrease") == 0){
			audioLevel = _max(0, startingLevel - 1);
		}else if(strcmp(param, "up") == 0 || strcmp(param, "increase") == 0){
			audioLevel = _min(2, startingLevel + 1);
		}
		Settings.get().volumeLevel = audioLevel;
		Settings.store();
		Playback.setVolume(audioLevelValues[audioLevel]);
		output->add(SampleStore::load(SampleGroup::Volume, "setTo"));
		output->add(SampleStore::load(SampleGroup::Levels, audioLevelNames[audioLevel]));
	}
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(output);
	Playback.setPlaybackDoneCallback([](){
		done();
	});
}

VolumeIntent::~VolumeIntent()
{
	
}

void VolumeIntent::loop(uint _time)
{
}

bool VolumeIntent::floatEqual(float a, float b)
{
	return fabs(a - b) < 0.1;
}