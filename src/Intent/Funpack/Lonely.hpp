#ifndef SPENCER_LONELY_HPP
#define SPENCER_LONELY_HPP

#include "FunpackIntent.h"

class FunpackLonely : public FunpackIntent {
public:
	FunpackLonely() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackLonely::responses[] = {};

#endif