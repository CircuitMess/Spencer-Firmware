#ifndef SPENCER_TELLSTORY_HPP
#define SPENCER_TELLSTORY_HPP

#include "FunpackIntent.h"

class FunpackTellstory : public FunpackIntent {
public:
	FunpackTellstory() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackTellstory::responses[] = {"funpack-tellstory0.mp3", "funpack-tellstory1.mp3", "funpack-tellstory2.mp3", "funpack-tellstory3.mp3"};

#endif