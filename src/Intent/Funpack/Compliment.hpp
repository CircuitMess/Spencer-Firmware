#ifndef SPENCER_COMPLIMENT_HPP
#define SPENCER_COMPLIMENT_HPP

#include "FunpackIntent.h"

class FunpackCompliment : public FunpackIntent {
public:
	FunpackCompliment() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCompliment::responses[] = {"funpack-compliment0.mp3", "funpack-compliment1.mp3", "funpack-compliment2.mp3", "funpack-compliment3.mp3"};

#endif