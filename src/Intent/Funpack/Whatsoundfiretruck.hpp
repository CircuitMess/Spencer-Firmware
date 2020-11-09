#ifndef SPENCER_WHATSOUNDFIRETRUCK_HPP
#define SPENCER_WHATSOUNDFIRETRUCK_HPP

#include "FunpackIntent.h"

class FunpackWhatsoundfiretruck : public FunpackIntent {
public:
	FunpackWhatsoundfiretruck() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWhatsoundfiretruck::responses[] = {"funpack-whatsoundfiretruck0.mp3", "funpack-whatsoundfiretruck1.mp3", "funpack-whatsoundfiretruck2.mp3", "funpack-whatsoundfiretruck3.mp3"};

#endif