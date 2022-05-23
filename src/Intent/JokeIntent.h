#ifndef SPENCER_JOKEINTENT_H
#define SPENCER_JOKEINTENT_H

#include <Arduino.h>
#include <vector>
#include "Intent.hpp"

class MatrixAnimGIF;
class AudioFileSource;

class JokeIntent: public Intent
{
public:
	JokeIntent();
	virtual ~JokeIntent() override;
	void loop(uint) override;
	void enter() override;
	void exit() override;
	
private:
	static const uint numJokes = 109;
	static std::vector<uint> jokeVector;
	AudioFileSource *file;
	bool badumFlag = 0;
	MatrixAnimGIF *anim = nullptr;
};


#endif