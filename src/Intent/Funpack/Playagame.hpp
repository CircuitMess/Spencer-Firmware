#ifndef SPENCER_PLAYAGAME_HPP
#define SPENCER_PLAYAGAME_HPP

#include "FunpackIntent.h"

class FunpackPlayagame : public FunpackIntent {
public:
	FunpackPlayagame() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackPlayagame::responses[] = {"funpack-playagame0.mp3", "funpack-playagame1.mp3", "funpack-playagame2.mp3", "funpack-playagame3.mp3"};

#endif