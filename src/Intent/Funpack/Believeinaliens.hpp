#ifndef SPENCER_BELIEVEINALIENS_HPP
#define SPENCER_BELIEVEINALIENS_HPP

#include "FunpackIntent.h"

class FunpackBelieveinaliens : public FunpackIntent {
public:
	FunpackBelieveinaliens() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackBelieveinaliens::responses[] = {};

#endif