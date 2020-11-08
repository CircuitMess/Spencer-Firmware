#ifndef SPENCER_TRUCK_HPP
#define SPENCER_TRUCK_HPP

#include "FunpackIntent.h"

class FunpackTruck : public FunpackIntent {
public:
	FunpackTruck() : FunpackIntent(responses, 3){}

private:
	static const char* responses[];

};

const char* FunpackTruck::responses[] = {"funpack-truck0.mp3", "funpack-truck1.mp3", "funpack-truck2.mp3"};

#endif