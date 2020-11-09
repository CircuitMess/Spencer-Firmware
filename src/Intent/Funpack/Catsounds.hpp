#ifndef SPENCER_CATSOUNDS_HPP
#define SPENCER_CATSOUNDS_HPP

#include "FunpackIntent.h"

class FunpackCatsounds : public FunpackIntent {
public:
	FunpackCatsounds() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCatsounds::responses[] = {};

#endif