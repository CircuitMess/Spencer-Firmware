#ifndef SPENCER_LONGTIMENOSEE_HPP
#define SPENCER_LONGTIMENOSEE_HPP

#include "FunpackIntent.h"

class FunpackLongtimenosee : public FunpackIntent {
public:
	FunpackLongtimenosee() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackLongtimenosee::responses[] = {"funpack-longtimenosee0.mp3", "funpack-longtimenosee1.mp3", "funpack-longtimenosee2.mp3", "funpack-longtimenosee3.mp3"};

#endif