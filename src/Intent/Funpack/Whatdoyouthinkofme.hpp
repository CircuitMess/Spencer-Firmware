#ifndef SPENCER_WHATDOYOUTHINKOFME_HPP
#define SPENCER_WHATDOYOUTHINKOFME_HPP

#include "FunpackIntent.h"

class FunpackWhatdoyouthinkofme : public FunpackIntent {
public:
	FunpackWhatdoyouthinkofme() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhatdoyouthinkofme::responses[] = {"funpack-whatdoyouthinkofme0.mp3", "funpack-whatdoyouthinkofme1.mp3", "funpack-whatdoyouthinkofme2.mp3", "funpack-whatdoyouthinkofme3.mp3"};

#endif