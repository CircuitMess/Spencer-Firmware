#ifndef SPENCER_DISLIKE_HPP
#define SPENCER_DISLIKE_HPP

#include "FunpackIntent.h"

class FunpackDislike : public FunpackIntent {
public:
	FunpackDislike() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackDislike::responses[] = {};

#endif