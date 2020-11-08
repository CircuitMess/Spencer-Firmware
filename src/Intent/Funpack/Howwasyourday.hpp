#ifndef SPENCER_HOWWASYOURDAY_HPP
#define SPENCER_HOWWASYOURDAY_HPP

#include "FunpackIntent.h"

class FunpackHowwasyourday : public FunpackIntent {
public:
	FunpackHowwasyourday() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHowwasyourday::responses[] = {"funpack-howwasyourday0.mp3", "funpack-howwasyourday1.mp3", "funpack-howwasyourday2.mp3", "funpack-howwasyourday3.mp3"};

#endif