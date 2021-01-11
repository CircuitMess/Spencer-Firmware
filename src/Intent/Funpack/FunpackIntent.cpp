#include "FunpackIntent.h"
#include <Audio/Playback.h>
#include <Spencer.h>

FunpackIntent::FunpackIntent(const char* responses[], uint8_t noResponses){
	uint i = rand() % noResponses;
	filePath = responses[i];
}

void FunpackIntent::loop(uint micros){
	if(!Playback.isRunning()){
		done();
	}
}

void FunpackIntent::enter()
{
	Playback.playMP3(filePath);
	LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-talk.gif")), true);
}

void FunpackIntent::exit()
{
	
}