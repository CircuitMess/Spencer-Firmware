#ifndef SPENCER_PACKAGE_HPP
#define SPENCER_PACKAGE_HPP

#include "FunpackIntent.h"

class FunpackPackage : public FunpackIntent {
public:
	FunpackPackage() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackPackage::responses[] = {"funpack-package0.mp3", "funpack-package1.mp3", "funpack-package2.mp3", "funpack-package3.mp3"};

#endif