#ifndef SPENCER_BUYABOAT_HPP
#define SPENCER_BUYABOAT_HPP

#include "FunpackIntent.h"

class FunpackBuyaboat : public FunpackIntent {
public:
	FunpackBuyaboat() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBuyaboat::responses[] = {"funpack-buyaboat0.mp3", "funpack-buyaboat1.mp3", "funpack-buyaboat2.mp3", "funpack-buyaboat3.mp3"};

#endif