#ifndef SPENCER_CATSOUNDS_HPP
#define SPENCER_CATSOUNDS_HPP

#include "FunpackIntent.h"

class FunpackCatsounds : public FunpackIntent {
public:
	FunpackCatsounds() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCatsounds::responses[] = {"funpack-catsounds0.mp3", "funpack-catsounds1.mp3", "funpack-catsounds2.mp3", "funpack-catsounds3.mp3"};

#endif