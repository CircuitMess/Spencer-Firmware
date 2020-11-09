#ifndef SPENCER_DONKEYSOUND_HPP
#define SPENCER_DONKEYSOUND_HPP

#include "FunpackIntent.h"

class FunpackDonkeysound : public FunpackIntent {
public:
	FunpackDonkeysound() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackDonkeysound::responses[] = {"funpack-donkeysound0.mp3", "funpack-donkeysound1.mp3", "funpack-donkeysound2.mp3", "funpack-donkeysound3.mp3"};

#endif