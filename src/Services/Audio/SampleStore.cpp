#include "SampleStore.h"
#include "AudioFileSourceSerialFlash.h"

const char* prefixes[6] = { "months", "numbers", "jokes", "generic", "time", "special" };

AudioFileSource* SampleStore::load(SampleGroup group, const char* label){
	char fileName[40];
	sprintf(fileName, "%s-%s.mp3", prefixes[(int) group], label);
	return new AudioFileSourceSerialFlash(fileName);
}
