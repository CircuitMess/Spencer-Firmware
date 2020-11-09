#ifndef SPENCER_SERANDE_HPP
#define SPENCER_SERANDE_HPP

#include "FunpackIntent.h"

class FunpackSerande : public FunpackIntent {
public:
	FunpackSerande() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackSerande::responses[] = {"funpack-serande0.mp3", "funpack-serande1.mp3", "funpack-serande2.mp3", "funpack-serande3.mp3"};

#endif