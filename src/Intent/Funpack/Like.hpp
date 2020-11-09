#ifndef SPENCER_LIKE_HPP
#define SPENCER_LIKE_HPP

#include "FunpackIntent.h"

class FunpackLike : public FunpackIntent {
public:
	FunpackLike() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackLike::responses[] = {"funpack-like0.mp3", "funpack-like1.mp3", "funpack-like2.mp3", "funpack-like3.mp3"};

#endif