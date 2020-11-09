#ifndef SPENCER_BEYOURBOYFRIEND_HPP
#define SPENCER_BEYOURBOYFRIEND_HPP

#include "FunpackIntent.h"

class FunpackBeyourboyfriend : public FunpackIntent {
public:
	FunpackBeyourboyfriend() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackBeyourboyfriend::responses[] = {"funpack-beyourboyfriend0.mp3", "funpack-beyourboyfriend1.mp3", "funpack-beyourboyfriend2.mp3", "funpack-beyourboyfriend3.mp3"};

#endif