#ifndef SPENCER_MERRYCHRISTMAS_HPP
#define SPENCER_MERRYCHRISTMAS_HPP

#include "FunpackIntent.h"

class FunpackMerrychristmas : public FunpackIntent {
public:
	FunpackMerrychristmas() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackMerrychristmas::responses[] = {"funpack-merrychristmas0.mp3", "funpack-merrychristmas1.mp3", "funpack-merrychristmas2.mp3", "funpack-merrychristmas3.mp3"};

#endif