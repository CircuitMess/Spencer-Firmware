#ifndef SPENCER_TV_HPP
#define SPENCER_TV_HPP

#include "FunpackIntent.h"

class FunpackTv : public FunpackIntent {
public:
	FunpackTv() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackTv::responses[] = {"funpack-tv0.mp3", "funpack-tv1.mp3", "funpack-tv2.mp3", "funpack-tv3.mp3"};

#endif