#ifndef SPENCER_BEAMMEUPSCOTTY_HPP
#define SPENCER_BEAMMEUPSCOTTY_HPP

#include "FunpackIntent.h"

class FunpackBeammeupscotty : public FunpackIntent {
public:
	FunpackBeammeupscotty() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackBeammeupscotty::responses[] = {};

#endif