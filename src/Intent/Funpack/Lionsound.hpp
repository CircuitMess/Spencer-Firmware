#ifndef SPENCER_LIONSOUND_HPP
#define SPENCER_LIONSOUND_HPP

#include "FunpackIntent.h"

class FunpackLionsound : public FunpackIntent {
public:
	FunpackLionsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackLionsound::responses[] = {"funpack-lionsound0.mp3", "funpack-lionsound1.mp3", "funpack-lionsound2.mp3", "funpack-lionsound3.mp3"};

#endif