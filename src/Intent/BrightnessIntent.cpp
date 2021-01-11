#include "BrightnessIntent.h"
#include <Spencer.h>
#include <Audio/Playback.h>
#include <Settings.h>
BrightnessIntent::BrightnessIntent(BrightnessValue value)
{
	startingLevel = Settings.get().brightnessLevel;
	param = value;
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
	
	switch (param)
	{
	case BrightnessValue::B_LO:
		brightnessLevel = 0;
		break;
	case BrightnessValue::B_HI:
		brightnessLevel = 2;
		break;
	case BrightnessValue::B_MEDIUM:
		brightnessLevel = 1;
		break;
	case BrightnessValue::B_INCREASE:
		brightnessLevel = _min(2, startingLevel + 1);
		break;
	case BrightnessValue::B_DECREASE:
		brightnessLevel = _max(0, startingLevel - 1);
		break;
	case BrightnessValue::B_NONE:
		output->add(SampleStore::load(SampleGroup::Volume, "unknown"));
		output->add(SampleStore::load(SampleGroup::Levels, "low"));
		output->add(SampleStore::load(SampleGroup::Levels, "medium"));
		output->add(SampleStore::load(SampleGroup::Generic, "and"));
		output->add(SampleStore::load(SampleGroup::Levels, "high"));
		output->add(SampleStore::load(SampleGroup::Brightness, "trySaying"));
		break;
	default:
		break;
	}
		
	if(param != BrightnessValue::B_NONE){
		Settings.get().brightnessLevel = brightnessLevel;
		Settings.store();
		LEDmatrix.setBrightness(brightnessLevelValues[brightnessLevel]);
		output->add(SampleStore::load(SampleGroup::Brightness, "setTo"));
		output->add(SampleStore::load(SampleGroup::Levels, brightnessLevelNames[brightnessLevel]));
	}

	LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-talk.gif")), true);
	Playback.playMP3(output);
	Playback.setPlaybackDoneCallback([](){
		done();
	});
}

void BrightnessIntent::exit()
{
	
}