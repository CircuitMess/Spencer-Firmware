#ifndef SPENCER_GOODNIGHT_HPP
#define SPENCER_GOODNIGHT_HPP

#include "FunpackIntent.h"

class FunpackGoodnight : public FunpackIntent {
public:
	FunpackGoodnight() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGoodnight::responses[] = {"funpack-goodnight0.mp3", "funpack-goodnight1.mp3", "funpack-goodnight2.mp3", "funpack-goodnight3.mp3"};

#endif