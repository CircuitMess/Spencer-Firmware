#ifndef SPENCER_DOABARRELROLL_HPP
#define SPENCER_DOABARRELROLL_HPP

#include "FunpackIntent.h"

class FunpackDoabarrelroll : public FunpackIntent {
public:
	FunpackDoabarrelroll() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackDoabarrelroll::responses[] = {"funpack-doabarrelroll0.mp3", "funpack-doabarrelroll1.mp3", "funpack-doabarrelroll2.mp3", "funpack-doabarrelroll3.mp3"};

#endif