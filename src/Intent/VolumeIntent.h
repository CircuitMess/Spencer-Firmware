#ifndef SPENCER_VOLUMEINTENT_H
#define SPENCER_VOLUMEINTENT_H

#include <Arduino.h>
#include "Intent.hpp"
class AudioFileSource;

class VolumeIntent: public Intent
{
public:
	VolumeIntent(void* _params);
	virtual ~VolumeIntent() override;
	void loop(uint _time) override;
private:
	const char* param;
	uint8_t startingLevel = 0;
	uint8_t audioLevel = 0;
	float audioLevelValues[3] = {0.1, 0.3, 1.0};
	const char* audioLevelNames[3] = {"low", "medium", "high"};
	bool floatEqual(float a, float b);
};


#endif