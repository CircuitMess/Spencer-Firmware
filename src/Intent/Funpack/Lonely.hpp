#ifndef SPENCER_LONELY_HPP
#define SPENCER_LONELY_HPP

#include "FunpackIntent.h"

class FunpackLonely : public FunpackIntent {
public:
	FunpackLonely() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackLonely::responses[] = {"funpack-lonely0.mp3", "funpack-lonely1.mp3", "funpack-lonely2.mp3", "funpack-lonely3.mp3"};

#endif