#ifndef SPENCER_BEATBOX_HPP
#define SPENCER_BEATBOX_HPP

#include "FunpackIntent.h"

class FunpackBeatbox : public FunpackIntent {
public:
	FunpackBeatbox() : FunpackIntent(responses, 3){}

private:
	static const char* responses[];

};

const char* FunpackBeatbox::responses[] = {"funpack-beatbox0.mp3", "funpack-beatbox1.mp3", "funpack-beatbox2.mp3"};

#endif