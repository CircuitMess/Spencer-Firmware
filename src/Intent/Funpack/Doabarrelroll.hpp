#ifndef SPENCER_DOABARRELROLL_HPP
#define SPENCER_DOABARRELROLL_HPP

#include "FunpackIntent.h"

class FunpackDoabarrelroll : public FunpackIntent {
public:
	FunpackDoabarrelroll() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackDoabarrelroll::responses[] = {};

#endif