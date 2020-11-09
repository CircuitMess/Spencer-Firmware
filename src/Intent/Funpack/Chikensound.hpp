#ifndef SPENCER_CHIKENSOUND_HPP
#define SPENCER_CHIKENSOUND_HPP

#include "FunpackIntent.h"

class FunpackChikensound : public FunpackIntent {
public:
	FunpackChikensound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackChikensound::responses[] = {"funpack-chikensound0.mp3", "funpack-chikensound1.mp3", "funpack-chikensound2.mp3", "funpack-chikensound3.mp3"};

#endif