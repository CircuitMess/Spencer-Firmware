#ifndef SPENCER_UMBRELLA_HPP
#define SPENCER_UMBRELLA_HPP

#include "FunpackIntent.h"

class FunpackUmbrella : public FunpackIntent {
public:
	FunpackUmbrella() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackUmbrella::responses[] = {};

#endif