#ifndef SPENCER_CALLMOM_HPP
#define SPENCER_CALLMOM_HPP

#include "FunpackIntent.h"

class FunpackCallmom : public FunpackIntent {
public:
	FunpackCallmom() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCallmom::responses[] = {"funpack-callmom0.mp3", "funpack-callmom1.mp3", "funpack-callmom2.mp3", "funpack-callmom3.mp3"};

#endif