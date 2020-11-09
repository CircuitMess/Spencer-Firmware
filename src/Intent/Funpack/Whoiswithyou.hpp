#ifndef SPENCER_WHOISWITHYOU_HPP
#define SPENCER_WHOISWITHYOU_HPP

#include "FunpackIntent.h"

class FunpackWhoiswithyou : public FunpackIntent {
public:
	FunpackWhoiswithyou() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackWhoiswithyou::responses[] = {};

#endif