#ifndef SPENCER_ACTORSINMOVIE_HPP
#define SPENCER_ACTORSINMOVIE_HPP

#include "FunpackIntent.h"

class FunpackActorsinmovie : public FunpackIntent {
public:
	FunpackActorsinmovie() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackActorsinmovie::responses[] = {};

#endif