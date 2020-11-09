#ifndef SPENCER_NOTBIRTHDAY_HPP
#define SPENCER_NOTBIRTHDAY_HPP

#include "FunpackIntent.h"

class FunpackNotbirthday : public FunpackIntent {
public:
	FunpackNotbirthday() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackNotbirthday::responses[] = {};

#endif