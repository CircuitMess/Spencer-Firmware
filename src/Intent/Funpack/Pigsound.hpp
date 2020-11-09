#ifndef SPENCER_PIGSOUND_HPP
#define SPENCER_PIGSOUND_HPP

#include "FunpackIntent.h"

class FunpackPigsound : public FunpackIntent {
public:
	FunpackPigsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackPigsound::responses[] = {};

#endif