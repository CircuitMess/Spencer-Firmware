#ifndef SPENCER_WHATDOYOUTHINKOFME_HPP
#define SPENCER_WHATDOYOUTHINKOFME_HPP

#include "FunpackIntent.h"

class FunpackWhatdoyouthinkofme : public FunpackIntent {
public:
	FunpackWhatdoyouthinkofme() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackWhatdoyouthinkofme::responses[] = {};

#endif