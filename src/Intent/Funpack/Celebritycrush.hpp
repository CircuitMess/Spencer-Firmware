#ifndef SPENCER_CELEBRITYCRUSH_HPP
#define SPENCER_CELEBRITYCRUSH_HPP

#include "FunpackIntent.h"

class FunpackCelebritycrush : public FunpackIntent {
public:
	FunpackCelebritycrush() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCelebritycrush::responses[] = {};

#endif