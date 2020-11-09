#ifndef SPENCER_GOODDAY_HPP
#define SPENCER_GOODDAY_HPP

#include "FunpackIntent.h"

class FunpackGoodday : public FunpackIntent {
public:
	FunpackGoodday() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGoodday::responses[] = {"funpack-goodday0.mp3", "funpack-goodday1.mp3", "funpack-goodday2.mp3", "funpack-goodday3.mp3"};

#endif