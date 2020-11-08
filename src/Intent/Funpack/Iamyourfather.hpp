#ifndef SPENCER_IAMYOURFATHER_HPP
#define SPENCER_IAMYOURFATHER_HPP

#include "FunpackIntent.h"

class FunpackIamyourfather : public FunpackIntent {
public:
	FunpackIamyourfather() : FunpackIntent(responses, 0){}

private:
	static const char* responses[];

};

const char* FunpackIamyourfather::responses[] = {};

#endif