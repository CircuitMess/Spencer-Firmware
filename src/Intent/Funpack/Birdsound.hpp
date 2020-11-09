#ifndef SPENCER_BIRDSOUND_HPP
#define SPENCER_BIRDSOUND_HPP

#include "FunpackIntent.h"

class FunpackBirdsound : public FunpackIntent {
public:
	FunpackBirdsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackBirdsound::responses[] = {};

#endif