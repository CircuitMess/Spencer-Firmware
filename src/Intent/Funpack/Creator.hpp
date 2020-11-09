#ifndef SPENCER_CREATOR_HPP
#define SPENCER_CREATOR_HPP

#include "FunpackIntent.h"

class FunpackCreator : public FunpackIntent {
public:
	FunpackCreator() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackCreator::responses[] = {"funpack-creator0.mp3", "funpack-creator1.mp3", "funpack-creator2.mp3", "funpack-creator3.mp3"};

#endif