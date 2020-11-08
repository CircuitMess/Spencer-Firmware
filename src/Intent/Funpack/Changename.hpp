#ifndef SPENCER_CHANGENAME_HPP
#define SPENCER_CHANGENAME_HPP

#include "FunpackIntent.h"

class FunpackChangename : public FunpackIntent {
public:
	FunpackChangename() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackChangename::responses[] = {"funpack-changename0.mp3", "funpack-changename1.mp3", "funpack-changename2.mp3", "funpack-changename3.mp3"};

#endif