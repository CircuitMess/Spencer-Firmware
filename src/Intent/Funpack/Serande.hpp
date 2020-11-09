#ifndef SPENCER_SERANDE_HPP
#define SPENCER_SERANDE_HPP

#include "FunpackIntent.h"

class FunpackSerande : public FunpackIntent {
public:
	FunpackSerande() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackSerande::responses[] = {};

#endif