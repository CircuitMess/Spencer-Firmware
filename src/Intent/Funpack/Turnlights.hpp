#ifndef SPENCER_TURNLIGHTS_HPP
#define SPENCER_TURNLIGHTS_HPP

#include "FunpackIntent.h"

class FunpackTurnlights : public FunpackIntent {
public:
	FunpackTurnlights() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackTurnlights::responses[] = {};

#endif