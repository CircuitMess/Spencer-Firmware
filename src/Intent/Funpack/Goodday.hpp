#ifndef SPENCER_GOODDAY_HPP
#define SPENCER_GOODDAY_HPP

#include "FunpackIntent.h"

class FunpackGoodday : public FunpackIntent {
public:
	FunpackGoodday() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackGoodday::responses[] = {};

#endif