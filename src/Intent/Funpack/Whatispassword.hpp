#ifndef SPENCER_WHATISPASSWORD_HPP
#define SPENCER_WHATISPASSWORD_HPP

#include "FunpackIntent.h"

class FunpackWhatispassword : public FunpackIntent {
public:
	FunpackWhatispassword() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackWhatispassword::responses[] = {};

#endif