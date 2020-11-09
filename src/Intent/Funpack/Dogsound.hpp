#ifndef SPENCER_DOGSOUND_HPP
#define SPENCER_DOGSOUND_HPP

#include "FunpackIntent.h"

class FunpackDogsound : public FunpackIntent {
public:
	FunpackDogsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackDogsound::responses[] = {"funpack-dogsound0.mp3", "funpack-dogsound1.mp3", "funpack-dogsound2.mp3", "funpack-dogsound3.mp3"};

#endif