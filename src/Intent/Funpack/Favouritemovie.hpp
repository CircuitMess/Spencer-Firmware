#ifndef SPENCER_FAVOURITEMOVIE_HPP
#define SPENCER_FAVOURITEMOVIE_HPP

#include "FunpackIntent.h"

class FunpackFavouritemovie : public FunpackIntent {
public:
	FunpackFavouritemovie() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFavouritemovie::responses[] = {"funpack-favouritemovie0.mp3", "funpack-favouritemovie1.mp3", "funpack-favouritemovie2.mp3", "funpack-favouritemovie3.mp3"};

#endif