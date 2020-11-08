#ifndef SPENCER_BELIEVEINLOVE_HPP
#define SPENCER_BELIEVEINLOVE_HPP

#include "FunpackIntent.h"

class FunpackBelieveinlove : public FunpackIntent {
public:
	FunpackBelieveinlove() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackBelieveinlove::responses[] = {};

#endif