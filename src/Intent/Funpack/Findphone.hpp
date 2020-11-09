#ifndef SPENCER_FINDPHONE_HPP
#define SPENCER_FINDPHONE_HPP

#include "FunpackIntent.h"

class FunpackFindphone : public FunpackIntent {
public:
	FunpackFindphone() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFindphone::responses[] = {"funpack-findphone0.mp3", "funpack-findphone1.mp3", "funpack-findphone2.mp3", "funpack-findphone3.mp3"};

#endif