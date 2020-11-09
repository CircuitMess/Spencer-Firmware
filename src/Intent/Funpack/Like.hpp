#ifndef SPENCER_LIKE_HPP
#define SPENCER_LIKE_HPP

#include "FunpackIntent.h"

class FunpackLike : public FunpackIntent {
public:
	FunpackLike() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackLike::responses[] = {};

#endif