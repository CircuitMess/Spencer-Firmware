#ifndef SPENCER_ORDERUBER_HPP
#define SPENCER_ORDERUBER_HPP

#include "FunpackIntent.h"

class FunpackOrderuber : public FunpackIntent {
public:
	FunpackOrderuber() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackOrderuber::responses[] = {"funpack-orderuber0.mp3", "funpack-orderuber1.mp3", "funpack-orderuber2.mp3", "funpack-orderuber3.mp3"};

#endif