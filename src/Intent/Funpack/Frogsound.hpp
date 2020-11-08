#ifndef SPENCER_FROGSOUND_HPP
#define SPENCER_FROGSOUND_HPP

#include "FunpackIntent.h"

class FunpackFrogsound : public FunpackIntent {
public:
	FunpackFrogsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackFrogsound::responses[] = {};

#endif