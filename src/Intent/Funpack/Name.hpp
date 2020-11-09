#ifndef SPENCER_NAME_HPP
#define SPENCER_NAME_HPP

#include "FunpackIntent.h"

class FunpackName : public FunpackIntent {
public:
	FunpackName() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackName::responses[] = {"funpack-name0.mp3", "funpack-name1.mp3", "funpack-name2.mp3", "funpack-name3.mp3"};

#endif