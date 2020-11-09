#ifndef SPENCER_OWLSOUND_HPP
#define SPENCER_OWLSOUND_HPP

#include "FunpackIntent.h"

class FunpackOwlsound : public FunpackIntent {
public:
	FunpackOwlsound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackOwlsound::responses[] = {};

#endif