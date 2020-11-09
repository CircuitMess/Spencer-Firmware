#ifndef SPENCER_MAKESANDWITCH_HPP
#define SPENCER_MAKESANDWITCH_HPP

#include "FunpackIntent.h"

class FunpackMakesandwitch : public FunpackIntent {
public:
	FunpackMakesandwitch() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackMakesandwitch::responses[] = {"funpack-makesandwitch0.mp3", "funpack-makesandwitch1.mp3", "funpack-makesandwitch2.mp3", "funpack-makesandwitch3.mp3"};

#endif