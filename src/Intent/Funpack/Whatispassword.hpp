#ifndef SPENCER_WHATISPASSWORD_HPP
#define SPENCER_WHATISPASSWORD_HPP

#include "FunpackIntent.h"

class FunpackWhatispassword : public FunpackIntent {
public:
	FunpackWhatispassword() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhatispassword::responses[] = {"funpack-whatispassword0.mp3", "funpack-whatispassword1.mp3", "funpack-whatispassword2.mp3", "funpack-whatispassword3.mp3"};

#endif