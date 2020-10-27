#include "JokeIntent.h"
#include "../Services/Audio/Audio.h"
JokeIntent::JokeIntent()
{

	uint jokeIndex = 0;
	bool jokeFound = 1;
	do
	{
		jokeIndex = random(0, 11);
		for(uint i = 0; i < jokeVector.size(); i++)
		{
			if(jokeVector[i] == jokeIndex)
			{
				jokeFound = 0;
				break;
			}
		}
	}
	while(!jokeFound);
	jokeVector.push_back(jokeIndex);
	if(jokeVector.size() == (int(numJokes/2) + 1))
	{
		jokeVector.erase(jokeVector.begin());
	}
	char buff[3] = {0};
	sprintf(buff, "%d", jokeIndex);
	file = SampleStore::load(SampleGroup::Jokes, buff);
	Audio.playMP3(file);
}
JokeIntent::~JokeIntent()
{

}
void JokeIntent::loop(uint micros)
{
	
}

