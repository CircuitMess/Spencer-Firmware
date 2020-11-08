#ifndef SPENCER_PIRATETALK_HPP
#define SPENCER_PIRATETALK_HPP

#include "FunpackIntent.h"

class FunpackPiratetalk : public FunpackIntent {
public:
	FunpackPiratetalk() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackPiratetalk::responses[] = {"funpack-piratetalk0.mp3", "funpack-piratetalk1.mp3", "funpack-piratetalk2.mp3", "funpack-piratetalk3.mp3"};

#endif