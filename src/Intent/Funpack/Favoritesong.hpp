#ifndef SPENCER_FAVORITESONG_HPP
#define SPENCER_FAVORITESONG_HPP

#include "FunpackIntent.h"

class FunpackFavoritesong : public FunpackIntent {
public:
	FunpackFavoritesong() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFavoritesong::responses[] = {"funpack-favoritesong0.mp3", "funpack-favoritesong1.mp3", "funpack-favoritesong2.mp3", "funpack-favoritesong3.mp3"};

#endif