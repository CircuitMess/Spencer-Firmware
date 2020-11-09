#ifndef SPENCER_PICKUPLINE_HPP
#define SPENCER_PICKUPLINE_HPP

#include "FunpackIntent.h"

class FunpackPickupline : public FunpackIntent {
public:
	FunpackPickupline() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackPickupline::responses[] = {"funpack-pickupline0.mp3", "funpack-pickupline1.mp3", "funpack-pickupline2.mp3", "funpack-pickupline3.mp3"};

#endif