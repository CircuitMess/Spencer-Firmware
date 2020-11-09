#ifndef SPENCER_COMPLIMENT_HPP
#define SPENCER_COMPLIMENT_HPP

#include "FunpackIntent.h"

class FunpackCompliment : public FunpackIntent {
public:
	FunpackCompliment() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackCompliment::responses[] = {};

#endif