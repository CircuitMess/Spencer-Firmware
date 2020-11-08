#ifndef SPENCER_PLAYAGAME_HPP
#define SPENCER_PLAYAGAME_HPP

#include "FunpackIntent.h"

class FunpackPlayagame : public FunpackIntent {
public:
	FunpackPlayagame() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackPlayagame::responses[] = {};

#endif