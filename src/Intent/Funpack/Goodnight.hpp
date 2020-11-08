#ifndef SPENCER_GOODNIGHT_HPP
#define SPENCER_GOODNIGHT_HPP

#include "FunpackIntent.h"

class FunpackGoodnight : public FunpackIntent {
public:
	FunpackGoodnight() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackGoodnight::responses[] = {};

#endif