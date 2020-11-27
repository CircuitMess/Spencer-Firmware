#ifndef SPENCER_BRIGHTNESSINTENT_H
#define SPENCER_BRIGHTNESSINTENT_H

#include <Arduino.h>
#include "Intent.hpp"
class AudioFileSource;

enum BrightnessValue{
	B_LO, B_MEDIUM, B_HI, B_INCREASE, B_DECREASE, B_NONE
};
class BrightnessIntent: public Intent
{
public:
	BrightnessIntent(BrightnessValue value);
	virtual ~BrightnessIntent() override;
	void loop(uint _time) override;
	void enter() override;
	void exit() override;
	
private:
	BrightnessValue param;
	uint8_t startingLevel = 0;
	uint8_t brightnessLevel = 0;
	uint8_t brightnessLevelValues[3] = {5, 20, 100};
	const char* brightnessLevelNames[3] = {"low", "medium", "high"};
	bool floatEqual(float a, float b);
};


#endif