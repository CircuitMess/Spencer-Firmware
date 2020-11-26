#include "FunpackIntent.h"
#include "../../Services/Audio/Playback.h"
#include "../../LEDmatrix/LEDmatrix.h"

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
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
}

void FunpackIntent::exit()
{
	
}