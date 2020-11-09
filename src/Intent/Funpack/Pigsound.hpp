#ifndef SPENCER_PIGSOUND_HPP
#define SPENCER_PIGSOUND_HPP

#include "FunpackIntent.h"

class FunpackPigsound : public FunpackIntent {
public:
	FunpackPigsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackPigsound::responses[] = {"funpack-pigsound0.mp3", "funpack-pigsound1.mp3", "funpack-pigsound2.mp3", "funpack-pigsound3.mp3"};

#endif