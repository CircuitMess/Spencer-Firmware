#include "JokeIntent.h"
#include <Audio/Playback.h>
#include <Spencer.h>
#include <Devices/Matrix/MatrixAnimGIF.h>

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
		char badum[8];
		sprintf(badum, "badum%d", badumNumber);
		Playback.playMP3(SampleStore::load(SampleGroup::Special, badum));
		Playback.setPlaybackDoneCallback([](){
			done();
		});

		delete anim;
		anim = new MatrixAnimGIF( new SerialFlashFileAdapter(random(0, 2) ? "GIF-laugh.gif" : "GIF-smile.gif"));
		LEDmatrix.startAnimation(anim);
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
	char buff[5] = {0};
	sprintf(buff, "%d", jokeIndex);
	file = SampleStore::load(SampleGroup::Jokes, buff);
	Playback.playMP3(file);

	anim = new MatrixAnimGIF(new SerialFlashFileAdapter("GIF-talk.gif"));
	LEDmatrix.startAnimation(anim);
}

void JokeIntent::exit()
{
	delete anim;
}