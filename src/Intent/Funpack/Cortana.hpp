#ifndef SPENCER_CORTANA_HPP
#define SPENCER_CORTANA_HPP

#include "FunpackIntent.h"

class FunpackCortana : public FunpackIntent {
public:
	FunpackCortana() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCortana::responses[] = {"funpack-cortana0.mp3", "funpack-cortana1.mp3", "funpack-cortana2.mp3", "funpack-cortana3.mp3"};

#endif