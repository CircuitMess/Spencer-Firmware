#ifndef SPENCER_TELLSTORY_HPP
#define SPENCER_TELLSTORY_HPP

#include "FunpackIntent.h"

class FunpackTellstory : public FunpackIntent {
public:
	FunpackTellstory() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackTellstory::responses[] = {};

#endif