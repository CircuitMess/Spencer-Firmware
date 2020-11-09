#ifndef SPENCER_TURKEYSOUND_HPP
#define SPENCER_TURKEYSOUND_HPP

#include "FunpackIntent.h"

class FunpackTurkeysound : public FunpackIntent {
public:
	FunpackTurkeysound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackTurkeysound::responses[] = {"funpack-turkeysound0.mp3", "funpack-turkeysound1.mp3", "funpack-turkeysound2.mp3", "funpack-turkeysound3.mp3"};

#endif