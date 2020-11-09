#ifndef SPENCER_AREYOUOK_HPP
#define SPENCER_AREYOUOK_HPP

#include "FunpackIntent.h"

class FunpackAreyouok : public FunpackIntent {
public:
	FunpackAreyouok() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackAreyouok::responses[] = {};

#endif