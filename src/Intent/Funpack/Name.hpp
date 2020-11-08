#ifndef SPENCER_NAME_HPP
#define SPENCER_NAME_HPP

#include "FunpackIntent.h"

class FunpackName : public FunpackIntent {
public:
	FunpackName() : FunpackIntent(responses, 2){}

private:
	static const char* responses[];

};

const char* FunpackName::responses[] = { "jokes-0.mp3", "jokes-1.mp3" };

#endif //SPENCER_NAME_HPP
