#ifndef SPENCER_GOODMORNING_HPP
#define SPENCER_GOODMORNING_HPP

#include "FunpackIntent.h"

class FunpackGoodmorning : public FunpackIntent {
public:
	FunpackGoodmorning() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackGoodmorning::responses[] = {};

#endif