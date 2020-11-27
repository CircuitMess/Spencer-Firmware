#ifndef SPENCER_VOLUMEINTENT_H
#define SPENCER_VOLUMEINTENT_H

#include <Arduino.h>
#include "Intent.hpp"
class AudioFileSource;

enum AudioValue{
	A_LO, A_MEDIUM, A_HI, A_INCREASE, A_DECREASE, A_NONE
};
class VolumeIntent: public Intent
{
public:
	VolumeIntent(AudioValue value);
	virtual ~VolumeIntent() override;
	void loop(uint _time) override;
	void enter() override;
	void exit() override;
	
private:
	AudioValue param;
	uint8_t startingLevel = 0;
	uint8_t audioLevel = 0;
	float audioLevelValues[3] = {0.1, 0.4, 1.0};
	const char* audioLevelNames[3] = {"low", "medium", "high"};
	bool floatEqual(float a, float b);
};


#endif