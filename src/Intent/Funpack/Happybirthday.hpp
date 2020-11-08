#ifndef SPENCER_HAPPYBIRTHDAY_HPP
#define SPENCER_HAPPYBIRTHDAY_HPP

#include "FunpackIntent.h"

class FunpackHappybirthday : public FunpackIntent {
public:
	FunpackHappybirthday() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackHappybirthday::responses[] = {};

#endif