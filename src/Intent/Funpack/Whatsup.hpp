#ifndef SPENCER_WHATSUP_HPP
#define SPENCER_WHATSUP_HPP

#include "FunpackIntent.h"

class FunpackWhatsup : public FunpackIntent {
public:
	FunpackWhatsup() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhatsup::responses[] = {"funpack-whatsup0.mp3", "funpack-whatsup1.mp3", "funpack-whatsup2.mp3", "funpack-whatsup3.mp3"};

#endif