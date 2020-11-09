#ifndef SPENCER_CHIKENSOUND_HPP
#define SPENCER_CHIKENSOUND_HPP

#include "FunpackIntent.h"

class FunpackChikensound : public FunpackIntent {
public:
	FunpackChikensound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackChikensound::responses[] = {};

#endif