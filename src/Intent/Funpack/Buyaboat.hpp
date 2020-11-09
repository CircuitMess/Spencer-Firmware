#ifndef SPENCER_BUYABOAT_HPP
#define SPENCER_BUYABOAT_HPP

#include "FunpackIntent.h"

class FunpackBuyaboat : public FunpackIntent {
public:
	FunpackBuyaboat() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackBuyaboat::responses[] = {};

#endif