#ifndef SPENCER_BEDTIMESTORY_HPP
#define SPENCER_BEDTIMESTORY_HPP

#include "FunpackIntent.h"

class FunpackBedtimestory : public FunpackIntent {
public:
	FunpackBedtimestory() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackBedtimestory::responses[] = {};

#endif