#ifndef SPENCER_HORSESOUND_HPP
#define SPENCER_HORSESOUND_HPP

#include "FunpackIntent.h"

class FunpackHorsesound : public FunpackIntent {
public:
	FunpackHorsesound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHorsesound::responses[] = {"funpack-horsesound0.mp3", "funpack-horsesound1.mp3", "funpack-horsesound2.mp3", "funpack-horsesound3.mp3"};

#endif