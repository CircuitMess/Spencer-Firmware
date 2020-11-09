#ifndef SPENCER_FINDRECIPE_HPP
#define SPENCER_FINDRECIPE_HPP

#include "FunpackIntent.h"

class FunpackFindrecipe : public FunpackIntent {
public:
	FunpackFindrecipe() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFindrecipe::responses[] = {"funpack-findrecipe0.mp3", "funpack-findrecipe1.mp3", "funpack-findrecipe2.mp3", "funpack-findrecipe3.mp3"};

#endif