#ifndef SPENCER_GIRLFRIEND_HPP
#define SPENCER_GIRLFRIEND_HPP

#include "FunpackIntent.h"

class FunpackGirlfriend : public FunpackIntent {
public:
	FunpackGirlfriend() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGirlfriend::responses[] = {"funpack-girlfriend0.mp3", "funpack-girlfriend1.mp3", "funpack-girlfriend2.mp3", "funpack-girlfriend3.mp3"};

#endif