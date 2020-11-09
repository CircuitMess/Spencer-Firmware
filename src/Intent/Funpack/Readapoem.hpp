#ifndef SPENCER_READAPOEM_HPP
#define SPENCER_READAPOEM_HPP

#include "FunpackIntent.h"

class FunpackReadapoem : public FunpackIntent {
public:
	FunpackReadapoem() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackReadapoem::responses[] = {};

#endif