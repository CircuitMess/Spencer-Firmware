#ifndef SPENCER_COWSOUND_HPP
#define SPENCER_COWSOUND_HPP

#include "FunpackIntent.h"

class FunpackCowsound : public FunpackIntent {
public:
	FunpackCowsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCowsound::responses[] = {};

#endif