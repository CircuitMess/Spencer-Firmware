#ifndef SPENCER_HIGHFIVE_HPP
#define SPENCER_HIGHFIVE_HPP

#include "FunpackIntent.h"

class FunpackHighfive : public FunpackIntent {
public:
	FunpackHighfive() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHighfive::responses[] = {"funpack-highfive0.mp3", "funpack-highfive1.mp3", "funpack-highfive2.mp3", "funpack-highfive3.mp3"};

#endif