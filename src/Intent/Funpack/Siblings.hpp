#ifndef SPENCER_SIBLINGS_HPP
#define SPENCER_SIBLINGS_HPP

#include "FunpackIntent.h"

class FunpackSiblings : public FunpackIntent {
public:
	FunpackSiblings() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackSiblings::responses[] = {"funpack-siblings0.mp3", "funpack-siblings1.mp3", "funpack-siblings2.mp3", "funpack-siblings3.mp3"};

#endif