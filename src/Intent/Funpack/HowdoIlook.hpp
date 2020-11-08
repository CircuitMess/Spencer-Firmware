#ifndef SPENCER_HOWDOILOOK_HPP
#define SPENCER_HOWDOILOOK_HPP

#include "FunpackIntent.h"

class FunpackHowdoilook : public FunpackIntent {
public:
	FunpackHowdoilook() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackHowdoilook::responses[] = {};

#endif