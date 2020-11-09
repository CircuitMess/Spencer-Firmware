#ifndef SPENCER_SIRI_HPP
#define SPENCER_SIRI_HPP

#include "FunpackIntent.h"

class FunpackSiri : public FunpackIntent {
public:
	FunpackSiri() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackSiri::responses[] = {"funpack-siri0.mp3", "funpack-siri1.mp3", "funpack-siri2.mp3", "funpack-siri3.mp3"};

#endif