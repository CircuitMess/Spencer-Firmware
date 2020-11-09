#ifndef SPENCER_BEAMMEUPSCOTTY_HPP
#define SPENCER_BEAMMEUPSCOTTY_HPP

#include "FunpackIntent.h"

class FunpackBeammeupscotty : public FunpackIntent {
public:
	FunpackBeammeupscotty() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBeammeupscotty::responses[] = {"funpack-beammeupscotty0.mp3", "funpack-beammeupscotty1.mp3", "funpack-beammeupscotty2.mp3", "funpack-beammeupscotty3.mp3"};

#endif