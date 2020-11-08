#ifndef SPENCER_WHATSOUNDFIRETRUCK_HPP
#define SPENCER_WHATSOUNDFIRETRUCK_HPP

#include "FunpackIntent.h"

class FunpackWhatsoundfiretruck : public FunpackIntent {
public:
	FunpackWhatsoundfiretruck() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackWhatsoundfiretruck::responses[] = {};

#endif