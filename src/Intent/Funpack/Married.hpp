#ifndef SPENCER_MARRIED_HPP
#define SPENCER_MARRIED_HPP

#include "FunpackIntent.h"

class FunpackMarried : public FunpackIntent {
public:
	FunpackMarried() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackMarried::responses[] = {"funpack-married0.mp3", "funpack-married1.mp3", "funpack-married2.mp3", "funpack-married3.mp3"};

#endif