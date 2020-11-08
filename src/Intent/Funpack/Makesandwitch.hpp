#ifndef SPENCER_MAKESANDWITCH_HPP
#define SPENCER_MAKESANDWITCH_HPP

#include "FunpackIntent.h"

class FunpackMakesandwitch : public FunpackIntent {
public:
	FunpackMakesandwitch() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackMakesandwitch::responses[] = {};

#endif