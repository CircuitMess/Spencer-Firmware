#ifndef SPENCER_HAPPYBIRTHDAY_HPP
#define SPENCER_HAPPYBIRTHDAY_HPP

#include "FunpackIntent.h"

class FunpackHappybirthday : public FunpackIntent {
public:
	FunpackHappybirthday() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHappybirthday::responses[] = {"funpack-happybirthday0.mp3", "funpack-happybirthday1.mp3", "funpack-happybirthday2.mp3", "funpack-happybirthday3.mp3"};

#endif