#ifndef SPENCER_GOODEVENING_HPP
#define SPENCER_GOODEVENING_HPP

#include "FunpackIntent.h"

class FunpackGoodevening : public FunpackIntent {
public:
	FunpackGoodevening() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackGoodevening::responses[] = {"funpack-goodevening0.mp3", "funpack-goodevening1.mp3", "funpack-goodevening2.mp3", "funpack-goodevening3.mp3"};

#endif