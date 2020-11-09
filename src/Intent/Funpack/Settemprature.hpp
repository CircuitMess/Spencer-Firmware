#ifndef SPENCER_SETTEMPRATURE_HPP
#define SPENCER_SETTEMPRATURE_HPP

#include "FunpackIntent.h"

class FunpackSettemprature : public FunpackIntent {
public:
	FunpackSettemprature() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackSettemprature::responses[] = {"funpack-settemprature0.mp3", "funpack-settemprature1.mp3", "funpack-settemprature2.mp3", "funpack-settemprature3.mp3"};

#endif