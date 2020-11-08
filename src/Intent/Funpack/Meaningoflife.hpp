#ifndef SPENCER_MEANINGOFLIFE_HPP
#define SPENCER_MEANINGOFLIFE_HPP

#include "FunpackIntent.h"

class FunpackMeaningoflife : public FunpackIntent {
public:
	FunpackMeaningoflife() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackMeaningoflife::responses[] = {"funpack-meaningoflife0.mp3", "funpack-meaningoflife1.mp3", "funpack-meaningoflife2.mp3", "funpack-meaningoflife3.mp3"};

#endif