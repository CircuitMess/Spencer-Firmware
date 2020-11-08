#ifndef SPENCER_WHEREDOYOUCOMEFROM_HPP
#define SPENCER_WHEREDOYOUCOMEFROM_HPP

#include "FunpackIntent.h"

class FunpackWheredoyoucomefrom : public FunpackIntent {
public:
	FunpackWheredoyoucomefrom() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackWheredoyoucomefrom::responses[] = {"funpack-wheredoyoucomefrom0.mp3", "funpack-wheredoyoucomefrom1.mp3", "funpack-wheredoyoucomefrom2.mp3", "funpack-wheredoyoucomefrom3.mp3"};

#endif