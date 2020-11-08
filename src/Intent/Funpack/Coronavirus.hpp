#ifndef SPENCER_CORONAVIRUS_HPP
#define SPENCER_CORONAVIRUS_HPP

#include "FunpackIntent.h"

class FunpackCoronavirus : public FunpackIntent {
public:
	FunpackCoronavirus() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCoronavirus::responses[] = {};

#endif