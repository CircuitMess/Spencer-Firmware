#ifndef SPENCER_WHOISPRESIDENT_HPP
#define SPENCER_WHOISPRESIDENT_HPP

#include "FunpackIntent.h"

class FunpackWhoispresident : public FunpackIntent {
public:
	FunpackWhoispresident() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhoispresident::responses[] = {"funpack-whoispresident0.mp3", "funpack-whoispresident1.mp3", "funpack-whoispresident2.mp3", "funpack-whoispresident3.mp3"};

#endif