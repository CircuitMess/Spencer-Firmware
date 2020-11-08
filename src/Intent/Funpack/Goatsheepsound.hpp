#ifndef SPENCER_GOATSHEEPSOUND_HPP
#define SPENCER_GOATSHEEPSOUND_HPP

#include "FunpackIntent.h"

class FunpackGoatsheepsound : public FunpackIntent {
public:
	FunpackGoatsheepsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackGoatsheepsound::responses[] = {};

#endif