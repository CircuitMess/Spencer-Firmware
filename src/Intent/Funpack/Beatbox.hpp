#ifndef SPENCER_BEATBOX_HPP
#define SPENCER_BEATBOX_HPP

#include "FunpackIntent.h"

class FunpackBeatbox : public FunpackIntent {
public:
	FunpackBeatbox() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBeatbox::responses[] = {"funpack-beatbox0.mp3", "funpack-beatbox1.mp3", "funpack-beatbox2.mp3", "funpack-beatbox3.mp3"};

#endif