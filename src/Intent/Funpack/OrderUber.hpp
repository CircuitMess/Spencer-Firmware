#ifndef SPENCER_ORDERUBER_HPP
#define SPENCER_ORDERUBER_HPP

#include "FunpackIntent.h"

class FunpackOrderuber : public FunpackIntent {
public:
	FunpackOrderuber() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackOrderuber::responses[] = {};

#endif