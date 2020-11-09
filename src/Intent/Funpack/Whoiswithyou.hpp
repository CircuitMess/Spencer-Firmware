#ifndef SPENCER_WHOISWITHYOU_HPP
#define SPENCER_WHOISWITHYOU_HPP

#include "FunpackIntent.h"

class FunpackWhoiswithyou : public FunpackIntent {
public:
	FunpackWhoiswithyou() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhoiswithyou::responses[] = {"funpack-whoiswithyou0.mp3", "funpack-whoiswithyou1.mp3", "funpack-whoiswithyou2.mp3", "funpack-whoiswithyou3.mp3"};

#endif