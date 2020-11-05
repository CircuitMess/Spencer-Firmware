#ifndef SPENCER_NAME_HPP
#define SPENCER_NAME_HPP

#include "FunpackIntent.h"

const char* FunpackNameResponses[] = { "jokes-0.mp3", "jokes-1.mp3" };

class FunpackName : public FunpackIntent {
public:
	FunpackName() : FUNPACK(FunpackNameResponses){}

};

#endif //SPENCER_NAME_HPP
