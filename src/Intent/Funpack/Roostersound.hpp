#ifndef SPENCER_ROOSTERSOUND_HPP
#define SPENCER_ROOSTERSOUND_HPP

#include "FunpackIntent.h"

class FunpackRoostersound : public FunpackIntent {
public:
	FunpackRoostersound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackRoostersound::responses[] = {};

#endif