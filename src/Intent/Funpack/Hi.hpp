#ifndef SPENCER_HI_HPP
#define SPENCER_HI_HPP

#include "FunpackIntent.h"

class FunpackHi : public FunpackIntent {
public:
	FunpackHi() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHi::responses[] = {"funpack-hi0.mp3", "funpack-hi1.mp3", "funpack-hi2.mp3", "funpack-hi3.mp3"};

#endif