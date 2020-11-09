#ifndef SPENCER_CRICKETSOUND_HPP
#define SPENCER_CRICKETSOUND_HPP

#include "FunpackIntent.h"

class FunpackCricketsound : public FunpackIntent {
public:
	FunpackCricketsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCricketsound::responses[] = {};

#endif