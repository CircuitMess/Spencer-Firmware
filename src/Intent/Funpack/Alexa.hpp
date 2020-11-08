#ifndef SPENCER_ALEXA_HPP
#define SPENCER_ALEXA_HPP

#include "FunpackIntent.h"

class FunpackAlexa : public FunpackIntent {
public:
	FunpackAlexa() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackAlexa::responses[] = {"funpack-alexa0.mp3", "funpack-alexa1.mp3", "funpack-alexa2.mp3", "funpack-alexa3.mp3"};

#endif