#ifndef SPENCER_LONGTIMENOSEE_HPP
#define SPENCER_LONGTIMENOSEE_HPP

#include "FunpackIntent.h"

class FunpackLongtimenosee : public FunpackIntent {
public:
	FunpackLongtimenosee() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackLongtimenosee::responses[] = {};

#endif