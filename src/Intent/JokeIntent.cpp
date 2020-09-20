#include "JokeIntent.h"
#include "../Services/Audio/Audio.h"
bool *jokeSaid = nullptr;
JokeIntent::JokeIntent(void* params) : Intent(params)
{
	if(jokeSaid == nullptr)
	{
		jokeSaid = new bool[numJokes];
		memset(jokeSaid, 0, numJokes);
	}
    bool allSaid = 1;
    for(uint8_t i = 0; i < numJokes; i++)
    {
        if(jokeSaid[i] == 0)
        {
            allSaid = 0;
            break;
        }
    }
    if(allSaid){
		file = SampleStore::load(SampleGroup::Jokes, "outOfJokes");
	}
    else
    {
		uint jokeIndex = 0;
        do
		{
            jokeIndex = random(0, 11);
		}
        while(jokeSaid[jokeIndex] == true);
		char buff[3] = {0};
		sprintf(buff, "%d", jokeIndex);
		file = SampleStore::load(SampleGroup::Jokes, buff);
    }
	audio.play(file);
}
JokeIntent::~JokeIntent()
{

}
void JokeIntent::loop()
{
	
}

