#ifndef SPENCER_ISTHISREALLIFE_HPP
#define SPENCER_ISTHISREALLIFE_HPP

#include "FunpackIntent.h"

class FunpackIsthisreallife : public FunpackIntent {
public:
	FunpackIsthisreallife() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackIsthisreallife::responses[] = {"funpack-isthisreallife0.mp3", "funpack-isthisreallife1.mp3", "funpack-isthisreallife2.mp3", "funpack-isthisreallife3.mp3"};

#endif