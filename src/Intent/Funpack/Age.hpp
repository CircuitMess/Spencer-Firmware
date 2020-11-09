#ifndef SPENCER_AGE_HPP
#define SPENCER_AGE_HPP

#include "FunpackIntent.h"

class FunpackAge : public FunpackIntent {
public:
	FunpackAge() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackAge::responses[] = {"funpack-age0.mp3", "funpack-age1.mp3", "funpack-age2.mp3", "funpack-age3.mp3"};

#endif