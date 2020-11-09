#ifndef SPENCER_BELIEVEINLOVE_HPP
#define SPENCER_BELIEVEINLOVE_HPP

#include "FunpackIntent.h"

class FunpackBelieveinlove : public FunpackIntent {
public:
	FunpackBelieveinlove() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBelieveinlove::responses[] = {"funpack-believeinlove0.mp3", "funpack-believeinlove1.mp3", "funpack-believeinlove2.mp3", "funpack-believeinlove3.mp3"};

#endif