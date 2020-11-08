#ifndef SPENCER_DIDYOUFART_HPP
#define SPENCER_DIDYOUFART_HPP

#include "FunpackIntent.h"

class FunpackDidyoufart : public FunpackIntent {
public:
	FunpackDidyoufart() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackDidyoufart::responses[] = {};

#endif