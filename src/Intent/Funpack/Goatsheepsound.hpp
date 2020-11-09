#ifndef SPENCER_GOATSHEEPSOUND_HPP
#define SPENCER_GOATSHEEPSOUND_HPP

#include "FunpackIntent.h"

class FunpackGoatsheepsound : public FunpackIntent {
public:
	FunpackGoatsheepsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGoatsheepsound::responses[] = {"funpack-goatsheepsound0.mp3", "funpack-goatsheepsound1.mp3", "funpack-goatsheepsound2.mp3", "funpack-goatsheepsound3.mp3"};

#endif