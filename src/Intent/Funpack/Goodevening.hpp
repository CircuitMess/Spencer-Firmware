#ifndef SPENCER_GOODEVENING_HPP
#define SPENCER_GOODEVENING_HPP

#include "FunpackIntent.h"

class FunpackGoodevening : public FunpackIntent {
public:
	FunpackGoodevening() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackGoodevening::responses[] = {};

#endif