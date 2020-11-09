#ifndef SPENCER_DIDYOUFART_HPP
#define SPENCER_DIDYOUFART_HPP

#include "FunpackIntent.h"

class FunpackDidyoufart : public FunpackIntent {
public:
	FunpackDidyoufart() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackDidyoufart::responses[] = {"funpack-didyoufart0.mp3", "funpack-didyoufart1.mp3", "funpack-didyoufart2.mp3", "funpack-didyoufart3.mp3"};

#endif