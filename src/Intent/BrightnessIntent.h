#ifndef SPENCER_BRIGHTNESSINTENT_H
#define SPENCER_BRIGHTNESSINTENT_H

#include <Arduino.h>
#include "Intent.hpp"
class AudioFileSource;

class BrightnessIntent: public Intent
{
public:
	BrightnessIntent(void* _params);
	virtual ~BrightnessIntent() override;
	void loop(uint _time) override;
private:
	const char* param;
	uint8_t startingLevel = 0;
	uint8_t brightnessLevel = 0;
	uint8_t brightnessLevelValues[3] = {20, 100, 255};
	const char* brightnessLevelNames[3] = {"low", "medium", "high"};
	bool floatEqual(float a, float b);
};


#endif