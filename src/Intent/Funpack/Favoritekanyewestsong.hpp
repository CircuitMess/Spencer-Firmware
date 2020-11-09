#ifndef SPENCER_FAVORITEKANYEWESTSONG_HPP
#define SPENCER_FAVORITEKANYEWESTSONG_HPP

#include "FunpackIntent.h"

class FunpackFavoritekanyewestsong : public FunpackIntent {
public:
	FunpackFavoritekanyewestsong() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackFavoritekanyewestsong::responses[] = {};

#endif