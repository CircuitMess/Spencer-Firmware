#ifndef SPENCER_HELP_HPP
#define SPENCER_HELP_HPP

#include "FunpackIntent.h"

class FunpackHelp : public FunpackIntent {
public:
	FunpackHelp() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHelp::responses[] = {"funpack-help0.mp3", "funpack-help1.mp3", "funpack-help2.mp3", "funpack-help3.mp3"};

#endif