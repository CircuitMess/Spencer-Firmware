#ifndef SPENCER_AREYOUSKYNET_HPP
#define SPENCER_AREYOUSKYNET_HPP

#include "FunpackIntent.h"

class FunpackAreyouskynet : public FunpackIntent {
public:
	FunpackAreyouskynet() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackAreyouskynet::responses[] = {};

#endif