#include "VolumeIntent.h"
#include "../LEDmatrix/LEDmatrix.h"
#include "../Services/Audio/Playback.h"
#include "../Settings.h"
VolumeIntent::VolumeIntent(AudioValue value)
{
	startingLevel = Settings.get().volumeLevel;
	param = value;
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

void VolumeIntent::enter()
{
	CompositeAudioFileSource* output = new CompositeAudioFileSource();

	switch (param)
	{
	case AudioValue::A_LO:
		audioLevel = 0;
		break;
	case AudioValue::A_HI:
		audioLevel = 2;
		break;
	case AudioValue::A_MEDIUM:
		audioLevel = 1;
		break;
	case AudioValue::A_INCREASE:
		audioLevel = _min(2, startingLevel + 1);
		break;
	case AudioValue::A_DECREASE:
		audioLevel = _max(0, startingLevel - 1);
		break;
	case AudioValue::A_NONE:
		output->add(SampleStore::load(SampleGroup::Volume, "unknown"));
		output->add(SampleStore::load(SampleGroup::Levels, "low"));
		output->add(SampleStore::load(SampleGroup::Levels, "medium"));
		output->add(SampleStore::load(SampleGroup::Generic, "and"));
		output->add(SampleStore::load(SampleGroup::Levels, "high"));
		output->add(SampleStore::load(SampleGroup::Volume, "trySaying"));
		break;
	default:
		break;
	}
		
	if(param != AudioValue::A_NONE){
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

void VolumeIntent::exit()
{
	
}