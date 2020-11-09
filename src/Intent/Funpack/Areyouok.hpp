#ifndef SPENCER_AREYOUOK_HPP
#define SPENCER_AREYOUOK_HPP

#include "FunpackIntent.h"

class FunpackAreyouok : public FunpackIntent {
public:
	FunpackAreyouok() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackAreyouok::responses[] = {"funpack-areyouok0.mp3", "funpack-areyouok1.mp3", "funpack-areyouok2.mp3", "funpack-areyouok3.mp3"};

#endif