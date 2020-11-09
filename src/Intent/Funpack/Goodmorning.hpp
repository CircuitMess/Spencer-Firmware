#ifndef SPENCER_GOODMORNING_HPP
#define SPENCER_GOODMORNING_HPP

#include "FunpackIntent.h"

class FunpackGoodmorning : public FunpackIntent {
public:
	FunpackGoodmorning() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGoodmorning::responses[] = {"funpack-goodmorning0.mp3", "funpack-goodmorning1.mp3", "funpack-goodmorning2.mp3", "funpack-goodmorning3.mp3"};

#endif