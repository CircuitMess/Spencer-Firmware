#ifndef SPENCER_FROGSOUND_HPP
#define SPENCER_FROGSOUND_HPP

#include "FunpackIntent.h"

class FunpackFrogsound : public FunpackIntent {
public:
	FunpackFrogsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFrogsound::responses[] = {"funpack-frogsound0.mp3", "funpack-frogsound1.mp3", "funpack-frogsound2.mp3", "funpack-frogsound3.mp3"};

#endif