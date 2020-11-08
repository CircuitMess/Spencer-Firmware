#ifndef SPENCER_CALLDIFFERENTLY_HPP
#define SPENCER_CALLDIFFERENTLY_HPP

#include "FunpackIntent.h"

class FunpackCalldifferently : public FunpackIntent {
public:
	FunpackCalldifferently() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCalldifferently::responses[] = {"funpack-calldifferently0.mp3", "funpack-calldifferently1.mp3", "funpack-calldifferently2.mp3", "funpack-calldifferently3.mp3"};

#endif