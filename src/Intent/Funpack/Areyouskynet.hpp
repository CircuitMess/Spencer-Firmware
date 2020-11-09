#ifndef SPENCER_AREYOUSKYNET_HPP
#define SPENCER_AREYOUSKYNET_HPP

#include "FunpackIntent.h"

class FunpackAreyouskynet : public FunpackIntent {
public:
	FunpackAreyouskynet() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackAreyouskynet::responses[] = {"funpack-areyouskynet0.mp3", "funpack-areyouskynet1.mp3", "funpack-areyouskynet2.mp3", "funpack-areyouskynet3.mp3"};

#endif