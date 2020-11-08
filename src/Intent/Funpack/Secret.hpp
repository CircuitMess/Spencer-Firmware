#ifndef SPENCER_SECRET_HPP
#define SPENCER_SECRET_HPP

#include "FunpackIntent.h"

class FunpackSecret : public FunpackIntent {
public:
	FunpackSecret() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackSecret::responses[] = {};

#endif