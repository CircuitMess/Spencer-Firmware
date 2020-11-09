#ifndef SPENCER_CELEBRITYCRUSH_HPP
#define SPENCER_CELEBRITYCRUSH_HPP

#include "FunpackIntent.h"

class FunpackCelebritycrush : public FunpackIntent {
public:
	FunpackCelebritycrush() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCelebritycrush::responses[] = {"funpack-celebritycrush0.mp3", "funpack-celebritycrush1.mp3", "funpack-celebritycrush2.mp3", "funpack-celebritycrush3.mp3"};

#endif