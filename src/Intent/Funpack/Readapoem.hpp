#ifndef SPENCER_READAPOEM_HPP
#define SPENCER_READAPOEM_HPP

#include "FunpackIntent.h"

class FunpackReadapoem : public FunpackIntent {
public:
	FunpackReadapoem() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackReadapoem::responses[] = {"funpack-readapoem0.mp3", "funpack-readapoem1.mp3", "funpack-readapoem2.mp3", "funpack-readapoem3.mp3"};

#endif