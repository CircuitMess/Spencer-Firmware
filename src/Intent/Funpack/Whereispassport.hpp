#ifndef SPENCER_WHEREISPASSPORT_HPP
#define SPENCER_WHEREISPASSPORT_HPP

#include "FunpackIntent.h"

class FunpackWhereispassport : public FunpackIntent {
public:
	FunpackWhereispassport() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhereispassport::responses[] = {"funpack-whereispassport0.mp3", "funpack-whereispassport1.mp3", "funpack-whereispassport2.mp3", "funpack-whereispassport3.mp3"};

#endif