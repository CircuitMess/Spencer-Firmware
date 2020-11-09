#ifndef SPENCER_COWSOUND_HPP
#define SPENCER_COWSOUND_HPP

#include "FunpackIntent.h"

class FunpackCowsound : public FunpackIntent {
public:
	FunpackCowsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCowsound::responses[] = {"funpack-cowsound0.mp3", "funpack-cowsound1.mp3", "funpack-cowsound2.mp3", "funpack-cowsound3.mp3"};

#endif