#ifndef SPENCER_SCARYSTORY_HPP
#define SPENCER_SCARYSTORY_HPP

#include "FunpackIntent.h"

class FunpackScarystory : public FunpackIntent {
public:
	FunpackScarystory() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackScarystory::responses[] = {"funpack-scarystory0.mp3", "funpack-scarystory1.mp3", "funpack-scarystory2.mp3", "funpack-scarystory3.mp3"};

#endif