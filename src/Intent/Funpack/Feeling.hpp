#ifndef SPENCER_FEELING_HPP
#define SPENCER_FEELING_HPP

#include "FunpackIntent.h"

class FunpackFeeling : public FunpackIntent {
public:
	FunpackFeeling() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFeeling::responses[] = {"funpack-feeling0.mp3", "funpack-feeling1.mp3", "funpack-feeling2.mp3", "funpack-feeling3.mp3"};

#endif