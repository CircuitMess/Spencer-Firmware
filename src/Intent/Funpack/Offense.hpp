#ifndef SPENCER_OFFENSE_HPP
#define SPENCER_OFFENSE_HPP

#include "FunpackIntent.h"

class FunpackOffense : public FunpackIntent {
public:
	FunpackOffense() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackOffense::responses[] = {"funpack-offense0.mp3", "funpack-offense1.mp3", "funpack-offense2.mp3", "funpack-offense3.mp3"};

#endif