#include "JokeIntent.h"
#include <Audio/Playback.h>
#include <Spencer.h>
std::vector<uint> JokeIntent::jokeVector;
JokeIntent::JokeIntent()
{
}
JokeIntent::~JokeIntent()
{

}
void JokeIntent::loop(uint micros)
{
	if(!Playback.isRunning() && !badumFlag)
	{
		uint8_t badumNumber = random(0, 4);
		char badum[7];
		sprintf(badum, "badum%d", badumNumber);
		Playback.playMP3(SampleStore::load(SampleGroup::Special, badum));
		Playback.setPlaybackDoneCallback([](){
			done();
		});
		LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter(random(0, 2) ? "GIF-laugh.gif" : "GIF-smile.gif")), true);
		badumFlag = true;
	}
}

void JokeIntent::enter()
{
	uint jokeIndex = 0;
	bool jokeFound = true;
	do
	{
		jokeIndex = random(0, numJokes);
		for(uint i = 0; i < jokeVector.size(); i++)
		{
			if(jokeVector[i] == jokeIndex)
			{
				jokeFound = false;
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
	char buff[4];
	sprintf(buff, "%d", jokeIndex);
	file = SampleStore::load(SampleGroup::Jokes, buff);
	Playback.playMP3(file);
	LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-talk.gif")), true);
}

void JokeIntent::exit()
{
	
}