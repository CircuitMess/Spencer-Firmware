#ifndef SPENCER_WHATCANYOUDO_HPP
#define SPENCER_WHATCANYOUDO_HPP

#include "FunpackIntent.h"

class FunpackWhatcanyoudo : public FunpackIntent {
public:
	FunpackWhatcanyoudo() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhatcanyoudo::responses[] = {"funpack-whatcanyoudo0.mp3", "funpack-whatcanyoudo1.mp3", "funpack-whatcanyoudo2.mp3", "funpack-whatcanyoudo3.mp3"};

#endif