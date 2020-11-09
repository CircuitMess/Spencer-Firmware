#ifndef SPENCER_DUCKGEESESOUND_HPP
#define SPENCER_DUCKGEESESOUND_HPP

#include "FunpackIntent.h"

class FunpackDuckgeesesound : public FunpackIntent {
public:
	FunpackDuckgeesesound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackDuckgeesesound::responses[] = {};

#endif