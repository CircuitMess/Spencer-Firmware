#include "FunpackIntent.h"
#include <Audio/Playback.h>
#include <Spencer.h>
#include <Devices/Matrix/MatrixAnimGIF.h>

FunpackIntent::FunpackIntent(const char* responses[], uint8_t noResponses){
	uint i = rand() % noResponses;
	filePath = responses[i];
}

void FunpackIntent::loop(uint micros){
	if(!Playback.isRunning()){
		done();
	}
}

void FunpackIntent::enter(){
	Playback.playMP3(filePath);
	anim = new MatrixAnimGIF(new SerialFlashFileAdapter("GIF-talk.gif"));
	LEDmatrix.startAnimation(anim);
}

void FunpackIntent::exit(){
	delete anim;
}