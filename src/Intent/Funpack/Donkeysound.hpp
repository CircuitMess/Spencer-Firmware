#ifndef SPENCER_DONKEYSOUND_HPP
#define SPENCER_DONKEYSOUND_HPP

#include "FunpackIntent.h"

class FunpackDonkeysound : public FunpackIntent {
public:
	FunpackDonkeysound() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackDonkeysound::responses[] = {};

#endif