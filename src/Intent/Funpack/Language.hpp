#ifndef SPENCER_LANGUAGE_HPP
#define SPENCER_LANGUAGE_HPP

#include "FunpackIntent.h"

class FunpackLanguage : public FunpackIntent {
public:
	FunpackLanguage() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackLanguage::responses[] = {"funpack-language0.mp3", "funpack-language1.mp3", "funpack-language2.mp3", "funpack-language3.mp3"};

#endif