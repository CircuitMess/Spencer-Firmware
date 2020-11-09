#ifndef SPENCER_FREETIME_HPP
#define SPENCER_FREETIME_HPP

#include "FunpackIntent.h"

class FunpackFreetime : public FunpackIntent {
public:
	FunpackFreetime() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFreetime::responses[] = {"funpack-freetime0.mp3", "funpack-freetime1.mp3", "funpack-freetime2.mp3", "funpack-freetime3.mp3"};

#endif