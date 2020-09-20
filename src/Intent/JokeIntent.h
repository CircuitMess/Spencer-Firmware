#ifndef SPENCER_JOKEINTENT_H
#define SPENCER_JOKEINTENT_H
#include <Arduino.h>
#include "Intent.hpp"
class AudioFileSource;
class JokeIntent: public Intent
{
public:
	JokeIntent(void* params);
	virtual ~JokeIntent() override;
private:
	const uint numJokes = 11;
	AudioFileSource *file;

};


#endif