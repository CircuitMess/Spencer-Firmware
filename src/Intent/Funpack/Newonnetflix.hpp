#ifndef SPENCER_NEWONNETFLIX_HPP
#define SPENCER_NEWONNETFLIX_HPP

#include "FunpackIntent.h"

class FunpackNewonnetflix : public FunpackIntent {
public:
	FunpackNewonnetflix() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackNewonnetflix::responses[] = {"funpack-newonnetflix0.mp3", "funpack-newonnetflix1.mp3", "funpack-newonnetflix2.mp3", "funpack-newonnetflix3.mp3"};

#endif