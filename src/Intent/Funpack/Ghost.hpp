#ifndef SPENCER_GHOST_HPP
#define SPENCER_GHOST_HPP

#include "FunpackIntent.h"

class FunpackGhost : public FunpackIntent {
public:
	FunpackGhost() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGhost::responses[] = {"funpack-ghost0.mp3", "funpack-ghost1.mp3", "funpack-ghost2.mp3", "funpack-ghost3.mp3"};

#endif