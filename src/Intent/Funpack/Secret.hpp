#ifndef SPENCER_SECRET_HPP
#define SPENCER_SECRET_HPP

#include "FunpackIntent.h"

class FunpackSecret : public FunpackIntent {
public:
	FunpackSecret() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackSecret::responses[] = {"funpack-secret0.mp3", "funpack-secret1.mp3", "funpack-secret2.mp3", "funpack-secret3.mp3"};

#endif