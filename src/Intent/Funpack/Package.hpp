#ifndef SPENCER_PACKAGE_HPP
#define SPENCER_PACKAGE_HPP

#include "FunpackIntent.h"

class FunpackPackage : public FunpackIntent {
public:
	FunpackPackage() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackPackage::responses[] = {};

#endif