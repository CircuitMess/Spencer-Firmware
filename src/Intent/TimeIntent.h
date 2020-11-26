#ifndef SPENCER_TIMEINTENT_H
#define SPENCER_TIMEINTENT_H

#include <Arduino.h>
#include "Intent.hpp"

class CompositeAudioFileSource;
enum TimeIntentType
{
	TIME, DATE
};
class TimeIntent: public Intent
{
public:
	TimeIntent(void* params);
	virtual ~TimeIntent() override;
	void loop(uint micros) override;
	void enter() override;
	void exit() override;

private:
	static TimeIntent *instance;
	CompositeAudioFileSource *speakFile;
	uint32_t elapsedMillis = millis();
	bool audioStopped = 0;
	TimeIntentType _params;
	char scrollingText[8];
	int8_t textCursor = 0;
	
};


#endif