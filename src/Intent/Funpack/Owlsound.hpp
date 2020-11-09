#ifndef SPENCER_OWLSOUND_HPP
#define SPENCER_OWLSOUND_HPP

#include "FunpackIntent.h"

class FunpackOwlsound : public FunpackIntent {
public:
	FunpackOwlsound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackOwlsound::responses[] = {"funpack-owlsound0.mp3", "funpack-owlsound1.mp3", "funpack-owlsound2.mp3", "funpack-owlsound3.mp3"};

#endif