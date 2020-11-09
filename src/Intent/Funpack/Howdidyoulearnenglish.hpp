#ifndef SPENCER_HOWDIDYOULEARNENGLISH_HPP
#define SPENCER_HOWDIDYOULEARNENGLISH_HPP

#include "FunpackIntent.h"

class FunpackHowdidyoulearnenglish : public FunpackIntent {
public:
	FunpackHowdidyoulearnenglish() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHowdidyoulearnenglish::responses[] = {"funpack-howdidyoulearnenglish0.mp3", "funpack-howdidyoulearnenglish1.mp3", "funpack-howdidyoulearnenglish2.mp3", "funpack-howdidyoulearnenglish3.mp3"};

#endif