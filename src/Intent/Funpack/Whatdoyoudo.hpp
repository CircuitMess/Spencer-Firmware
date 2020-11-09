#ifndef SPENCER_WHATDOYOUDO_HPP
#define SPENCER_WHATDOYOUDO_HPP

#include "FunpackIntent.h"

class FunpackWhatdoyoudo : public FunpackIntent {
public:
	FunpackWhatdoyoudo() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhatdoyoudo::responses[] = {"funpack-whatdoyoudo0.mp3", "funpack-whatdoyoudo1.mp3", "funpack-whatdoyoudo2.mp3", "funpack-whatdoyoudo3.mp3"};

#endif