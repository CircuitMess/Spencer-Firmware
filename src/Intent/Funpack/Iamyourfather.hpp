#ifndef SPENCER_IAMYOURFATHER_HPP
#define SPENCER_IAMYOURFATHER_HPP

#include "FunpackIntent.h"

class FunpackIamyourfather : public FunpackIntent {
public:
	FunpackIamyourfather() : FunpackIntent(responses, 4){}

private:
	static const char* responses[];

};

const char* FunpackIamyourfather::responses[] = {"funpack-iamyourfather0.mp3", "funpack-iamyourfather1.mp3", "funpack-iamyourfather2.mp3", "funpack-iamyourfather3.mp3"};

#endif