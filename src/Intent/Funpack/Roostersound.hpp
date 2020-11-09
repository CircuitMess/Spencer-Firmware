#ifndef SPENCER_ROOSTERSOUND_HPP
#define SPENCER_ROOSTERSOUND_HPP

#include "FunpackIntent.h"

class FunpackRoostersound : public FunpackIntent {
public:
	FunpackRoostersound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackRoostersound::responses[] = {"funpack-roostersound0.mp3", "funpack-roostersound1.mp3", "funpack-roostersound2.mp3", "funpack-roostersound3.mp3"};

#endif