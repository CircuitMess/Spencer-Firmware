#ifndef SPENCER_UMBRELLA_HPP
#define SPENCER_UMBRELLA_HPP

#include "FunpackIntent.h"

class FunpackUmbrella : public FunpackIntent {
public:
	FunpackUmbrella() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackUmbrella::responses[] = {"funpack-umbrella0.mp3", "funpack-umbrella1.mp3", "funpack-umbrella2.mp3", "funpack-umbrella3.mp3"};

#endif