#ifndef SPENCER_MERRYCHRISTMAS_HPP
#define SPENCER_MERRYCHRISTMAS_HPP

#include "FunpackIntent.h"

class FunpackMerrychristmas : public FunpackIntent {
public:
	FunpackMerrychristmas() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackMerrychristmas::responses[] = {};

#endif