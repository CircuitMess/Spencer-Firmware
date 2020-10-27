#ifndef SPENCER_JOKEINTENT_H
#define SPENCER_JOKEINTENT_H

#include <Arduino.h>
#include <vector>
#include "Intent.hpp"

class AudioFileSource;

class JokeIntent: public Intent
{
public:
	JokeIntent();
	virtual ~JokeIntent() override;
	void loop(uint) override;
private:
	static const uint numJokes = 11;
	std::vector<uint> jokeVector;
	AudioFileSource *file;

};


#endif