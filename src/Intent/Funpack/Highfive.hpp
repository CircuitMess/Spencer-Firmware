#ifndef SPENCER_HIGHFIVE_HPP
#define SPENCER_HIGHFIVE_HPP

#include "FunpackIntent.h"

class FunpackHighfive : public FunpackIntent {
public:
	FunpackHighfive() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackHighfive::responses[] = {};

#endif