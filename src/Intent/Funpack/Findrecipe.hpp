#ifndef SPENCER_FINDRECIPE_HPP
#define SPENCER_FINDRECIPE_HPP

#include "FunpackIntent.h"

class FunpackFindrecipe : public FunpackIntent {
public:
	FunpackFindrecipe() : FunpackIntent(responses, 1){}

private:
	static const char* responses[];

};

const char* FunpackFindrecipe::responses[] = {"funpack-findrecipe0.mp3"};

#endif