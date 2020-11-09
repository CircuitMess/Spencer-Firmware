#ifndef SPENCER_FINDPHONE_HPP
#define SPENCER_FINDPHONE_HPP

#include "FunpackIntent.h"

class FunpackFindphone : public FunpackIntent {
public:
	FunpackFindphone() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackFindphone::responses[] = {};

#endif