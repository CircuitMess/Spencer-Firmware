#ifndef SPENCER_HORSESOUND_HPP
#define SPENCER_HORSESOUND_HPP

#include "FunpackIntent.h"

class FunpackHorsesound : public FunpackIntent {
public:
	FunpackHorsesound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackHorsesound::responses[] = {};

#endif