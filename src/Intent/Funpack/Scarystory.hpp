#ifndef SPENCER_SCARYSTORY_HPP
#define SPENCER_SCARYSTORY_HPP

#include "FunpackIntent.h"

class FunpackScarystory : public FunpackIntent {
public:
	FunpackScarystory() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackScarystory::responses[] = {};

#endif