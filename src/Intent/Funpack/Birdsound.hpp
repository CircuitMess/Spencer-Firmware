#ifndef SPENCER_BIRDSOUND_HPP
#define SPENCER_BIRDSOUND_HPP

#include "FunpackIntent.h"

class FunpackBirdsound : public FunpackIntent {
public:
	FunpackBirdsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBirdsound::responses[] = {"funpack-birdsound0.mp3", "funpack-birdsound1.mp3", "funpack-birdsound2.mp3", "funpack-birdsound3.mp3"};

#endif