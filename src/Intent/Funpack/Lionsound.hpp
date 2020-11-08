#ifndef SPENCER_LIONSOUND_HPP
#define SPENCER_LIONSOUND_HPP

#include "FunpackIntent.h"

class FunpackLionsound : public FunpackIntent {
public:
	FunpackLionsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackLionsound::responses[] = {};

#endif