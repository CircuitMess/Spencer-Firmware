#ifndef SPENCER_DUCKGEESESOUND_HPP
#define SPENCER_DUCKGEESESOUND_HPP

#include "FunpackIntent.h"

class FunpackDuckgeesesound : public FunpackIntent {
public:
	FunpackDuckgeesesound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackDuckgeesesound::responses[] = {"funpack-duckgeesesound0.mp3", "funpack-duckgeesesound1.mp3", "funpack-duckgeesesound2.mp3", "funpack-duckgeesesound3.mp3"};

#endif