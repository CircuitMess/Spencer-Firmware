#include "SampleStore.h"
#include "AudioFileSourceSerialFlash.h"
const char *suffixes[7] = {"months", "numbers", "jokes", "generic", "time", "special", "weather"};
AudioFileSource* SampleStore::load(SampleGroup group, char* label)
{
	char fileName[40];
	sprintf(fileName, "%s-%s.mp3", prefixes[(int) group], label);
	return new AudioFileSourceSerialFlash(fileName);
}
