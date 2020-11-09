#ifndef SPENCER_BELIEVEINALIENS_HPP
#define SPENCER_BELIEVEINALIENS_HPP

#include "FunpackIntent.h"

class FunpackBelieveinaliens : public FunpackIntent {
public:
	FunpackBelieveinaliens() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBelieveinaliens::responses[] = {"funpack-believeinaliens0.mp3", "funpack-believeinaliens1.mp3", "funpack-believeinaliens2.mp3", "funpack-believeinaliens3.mp3"};

#endif