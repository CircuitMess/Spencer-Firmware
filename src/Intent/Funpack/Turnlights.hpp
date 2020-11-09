#ifndef SPENCER_TURNLIGHTS_HPP
#define SPENCER_TURNLIGHTS_HPP

#include "FunpackIntent.h"

class FunpackTurnlights : public FunpackIntent {
public:
	FunpackTurnlights() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackTurnlights::responses[] = {"funpack-turnlights0.mp3", "funpack-turnlights1.mp3", "funpack-turnlights2.mp3", "funpack-turnlights3.mp3"};

#endif