#ifndef SPENCER_WHATISYOURQUEST_HPP
#define SPENCER_WHATISYOURQUEST_HPP

#include "FunpackIntent.h"

class FunpackWhatisyourquest : public FunpackIntent {
public:
	FunpackWhatisyourquest() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhatisyourquest::responses[] = {"funpack-whatisyourquest0.mp3", "funpack-whatisyourquest1.mp3", "funpack-whatisyourquest2.mp3", "funpack-whatisyourquest3.mp3"};

#endif