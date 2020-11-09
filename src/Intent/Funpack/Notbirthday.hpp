#ifndef SPENCER_NOTBIRTHDAY_HPP
#define SPENCER_NOTBIRTHDAY_HPP

#include "FunpackIntent.h"

class FunpackNotbirthday : public FunpackIntent {
public:
	FunpackNotbirthday() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackNotbirthday::responses[] = {"funpack-notbirthday0.mp3", "funpack-notbirthday1.mp3", "funpack-notbirthday2.mp3", "funpack-notbirthday3.mp3"};

#endif