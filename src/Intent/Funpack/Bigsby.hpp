#ifndef SPENCER_BIGSBY_HPP
#define SPENCER_BIGSBY_HPP

#include "FunpackIntent.h"

class FunpackBigsby : public FunpackIntent {
public:
	FunpackBigsby() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBigsby::responses[] = {"funpack-bigsby0.mp3", "funpack-bigsby1.mp3", "funpack-bigsby2.mp3", "funpack-bigsby3.mp3"};

#endif