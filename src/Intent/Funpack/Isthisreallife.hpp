#ifndef SPENCER_ISTHISREALLIFE_HPP
#define SPENCER_ISTHISREALLIFE_HPP

#include "FunpackIntent.h"

class FunpackIsthisreallife : public FunpackIntent {
public:
	FunpackIsthisreallife() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackIsthisreallife::responses[] = {};

#endif