#ifndef SPENCER_SINGMEASONG_HPP
#define SPENCER_SINGMEASONG_HPP

#include "FunpackIntent.h"

class FunpackSingmeasong : public FunpackIntent {
public:
	FunpackSingmeasong() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackSingmeasong::responses[] = {"funpack-singmeasong0.mp3", "funpack-singmeasong1.mp3", "funpack-singmeasong2.mp3", "funpack-singmeasong3.mp3"};

#endif