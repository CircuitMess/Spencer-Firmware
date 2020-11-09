#ifndef SPENCER_HI_HPP
#define SPENCER_HI_HPP

#include "FunpackIntent.h"

class FunpackHi : public FunpackIntent {
public:
	FunpackHi() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackHi::responses[] = {};

#endif