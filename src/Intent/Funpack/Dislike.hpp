#ifndef SPENCER_DISLIKE_HPP
#define SPENCER_DISLIKE_HPP

#include "FunpackIntent.h"

class FunpackDislike : public FunpackIntent {
public:
	FunpackDislike() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackDislike::responses[] = {"funpack-dislike0.mp3", "funpack-dislike1.mp3", "funpack-dislike2.mp3", "funpack-dislike3.mp3"};

#endif