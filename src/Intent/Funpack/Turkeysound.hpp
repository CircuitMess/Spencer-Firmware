#ifndef SPENCER_TURKEYSOUND_HPP
#define SPENCER_TURKEYSOUND_HPP

#include "FunpackIntent.h"

class FunpackTurkeysound : public FunpackIntent {
public:
	FunpackTurkeysound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackTurkeysound::responses[] = {};

#endif