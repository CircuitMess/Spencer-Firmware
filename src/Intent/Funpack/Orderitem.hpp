#ifndef SPENCER_ORDERITEM_HPP
#define SPENCER_ORDERITEM_HPP

#include "FunpackIntent.h"

class FunpackOrderitem : public FunpackIntent {
public:
	FunpackOrderitem() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackOrderitem::responses[] = {};

#endif