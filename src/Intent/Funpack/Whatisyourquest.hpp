#ifndef SPENCER_WHATISYOURQUEST_HPP
#define SPENCER_WHATISYOURQUEST_HPP

#include "FunpackIntent.h"

class FunpackWhatisyourquest : public FunpackIntent {
public:
	FunpackWhatisyourquest() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackWhatisyourquest::responses[] = {};

#endif