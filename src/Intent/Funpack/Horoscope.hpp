#ifndef SPENCER_HOROSCOPE_HPP
#define SPENCER_HOROSCOPE_HPP

#include "FunpackIntent.h"

class FunpackHoroscope : public FunpackIntent {
public:
	FunpackHoroscope() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackHoroscope::responses[] = {"funpack-horoscope0.mp3", "funpack-horoscope1.mp3", "funpack-horoscope2.mp3", "funpack-horoscope3.mp3"};

#endif