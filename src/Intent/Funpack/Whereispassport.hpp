#ifndef SPENCER_WHEREISPASSPORT_HPP
#define SPENCER_WHEREISPASSPORT_HPP

#include "FunpackIntent.h"

class FunpackWhereispassport : public FunpackIntent {
public:
	FunpackWhereispassport() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackWhereispassport::responses[] = {};

#endif