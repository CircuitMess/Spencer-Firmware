#ifndef SPENCER_CALLMOM_HPP
#define SPENCER_CALLMOM_HPP

#include "FunpackIntent.h"

class FunpackCallmom : public FunpackIntent {
public:
	FunpackCallmom() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCallmom::responses[] = {};

#endif