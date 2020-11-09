#ifndef SPENCER_BOYFRIEND_HPP
#define SPENCER_BOYFRIEND_HPP

#include "FunpackIntent.h"

class FunpackBoyfriend : public FunpackIntent {
public:
	FunpackBoyfriend() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBoyfriend::responses[] = {"funpack-boyfriend0.mp3", "funpack-boyfriend1.mp3", "funpack-boyfriend2.mp3", "funpack-boyfriend3.mp3"};

#endif