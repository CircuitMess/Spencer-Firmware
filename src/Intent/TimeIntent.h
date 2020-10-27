#ifndef SPENCER_TIMEINTENT_H
#define SPENCER_TIMEINTENT_H
#include <Arduino.h>
#include "Intent.hpp"
class CompositeAudioFileSource;
enum TimeIntentType
{
	TIME, DATE
};
struct TimeIntentParam
{
	TimeIntentType type;
	uint unixTime;
};
class TimeIntent: public Intent
{
public:
	TimeIntent(void* params);
	virtual ~TimeIntent() override;
	void loop(uint micros) override;
private:
	CompositeAudioFileSource *speakFile;
	
};


#endif