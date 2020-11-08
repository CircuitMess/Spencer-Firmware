#ifndef SPENCER_DOGSOUND_HPP
#define SPENCER_DOGSOUND_HPP

#include "FunpackIntent.h"

class FunpackDogsound : public FunpackIntent {
public:
	FunpackDogsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackDogsound::responses[] = {};

#endif