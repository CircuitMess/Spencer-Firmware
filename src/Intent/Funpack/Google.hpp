#ifndef SPENCER_GOOGLE_HPP
#define SPENCER_GOOGLE_HPP

#include "FunpackIntent.h"

class FunpackGoogle : public FunpackIntent {
public:
	FunpackGoogle() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGoogle::responses[] = {"funpack-google0.mp3", "funpack-google1.mp3", "funpack-google2.mp3", "funpack-google3.mp3"};

#endif