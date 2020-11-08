#ifndef SPENCER_MOSQUITOSOUND_HPP
#define SPENCER_MOSQUITOSOUND_HPP

#include "FunpackIntent.h"

class FunpackMosquitosound : public FunpackIntent {
public:
	FunpackMosquitosound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackMosquitosound::responses[] = {};

#endif