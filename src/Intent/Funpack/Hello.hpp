#ifndef SPENCER_HELLO_HPP
#define SPENCER_HELLO_HPP

#include "FunpackIntent.h"

class FunpackHello : public FunpackIntent {
public:
	FunpackHello() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHello::responses[] = {"funpack-hello0.mp3", "funpack-hello1.mp3", "funpack-hello2.mp3", "funpack-hello3.mp3"};

#endif