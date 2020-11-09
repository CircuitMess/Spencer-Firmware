#ifndef SPENCER_ANGRYCROWD_HPP
#define SPENCER_ANGRYCROWD_HPP

#include "FunpackIntent.h"

class FunpackAngrycrowd : public FunpackIntent {
public:
	FunpackAngrycrowd() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackAngrycrowd::responses[] = {"funpack-angrycrowd0.mp3", "funpack-angrycrowd1.mp3", "funpack-angrycrowd2.mp3", "funpack-angrycrowd3.mp3"};

#endif