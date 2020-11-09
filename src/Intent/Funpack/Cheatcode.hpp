#ifndef SPENCER_CHEATCODE_HPP
#define SPENCER_CHEATCODE_HPP

#include "FunpackIntent.h"

class FunpackCheatcode : public FunpackIntent {
public:
	FunpackCheatcode() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCheatcode::responses[] = {"funpack-cheatcode0.mp3", "funpack-cheatcode1.mp3", "funpack-cheatcode2.mp3", "funpack-cheatcode3.mp3"};

#endif