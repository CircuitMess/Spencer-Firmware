#ifndef SPENCER_PICKUPLINE_HPP
#define SPENCER_PICKUPLINE_HPP

#include "FunpackIntent.h"

class FunpackPickupline : public FunpackIntent {
public:
	FunpackPickupline() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackPickupline::responses[] = {};

#endif