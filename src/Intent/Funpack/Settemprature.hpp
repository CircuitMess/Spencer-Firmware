#ifndef SPENCER_SETTEMPRATURE_HPP
#define SPENCER_SETTEMPRATURE_HPP

#include "FunpackIntent.h"

class FunpackSettemprature : public FunpackIntent {
public:
	FunpackSettemprature() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackSettemprature::responses[] = {};

#endif