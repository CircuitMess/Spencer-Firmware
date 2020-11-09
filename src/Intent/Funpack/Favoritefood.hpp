#ifndef SPENCER_FAVORITEFOOD_HPP
#define SPENCER_FAVORITEFOOD_HPP

#include "FunpackIntent.h"

class FunpackFavoritefood : public FunpackIntent {
public:
	FunpackFavoritefood() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackFavoritefood::responses[] = {"funpack-favoritefood0.mp3", "funpack-favoritefood1.mp3", "funpack-favoritefood2.mp3", "funpack-favoritefood3.mp3"};

#endif