#ifndef SPENCER_TV_HPP
#define SPENCER_TV_HPP

#include "FunpackIntent.h"

class FunpackTv : public FunpackIntent {
public:
	FunpackTv() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackTv::responses[] = {};

#endif