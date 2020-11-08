#ifndef SPENCER_CHEATCODE_HPP
#define SPENCER_CHEATCODE_HPP

#include "FunpackIntent.h"

class FunpackCheatcode : public FunpackIntent {
public:
	FunpackCheatcode() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCheatcode::responses[] = {};

#endif