#include "JokeIntent.h"
#include "../Services/Audio/Playback.h"
#include "../LEDmatrix/LEDmatrix.h"
JokeIntent::JokeIntent()
{
	randomSeed(micros()*millis());
	uint jokeIndex = 0;
	bool jokeFound = 1;
	do
	{
		jokeIndex = random(0, numJokes);
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
	char buff[5] = {0};
	sprintf(buff, "%d", jokeIndex);
	file = SampleStore::load(SampleGroup::Jokes, buff);
	Playback.playMP3(file);
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), 1);
}
JokeIntent::~JokeIntent()
{

}
void JokeIntent::loop(uint micros)
{
	if(!Playback.isRunning() && !badumFlag)
	{
		uint8_t badumNumber = random(0, 4);
		char badum[8];
		sprintf(badum, "badum%d", badumNumber);
		Playback.playMP3(SampleStore::load(SampleGroup::Special, badum));
		Playback.setPlaybackDoneCallback([](){
			done();
		});
		LEDmatrix.startAnimation(new Animation("GIF-laugh.gif"), 1);
		badumFlag = 1;
	}
}

