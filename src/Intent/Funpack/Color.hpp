#ifndef SPENCER_COLOR_HPP
#define SPENCER_COLOR_HPP

#include "FunpackIntent.h"

class FunpackColor : public FunpackIntent {
public:
	FunpackColor() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackColor::responses[] = {"funpack-color0.mp3", "funpack-color1.mp3", "funpack-color2.mp3", "funpack-color3.mp3"};

#endif