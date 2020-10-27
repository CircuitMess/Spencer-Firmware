#include "SampleStore.h"
#include "AudioFileSourceSerialFlash.h"
const char *suffixes[5] = {"months", "numbers", "jokes", "generic", "time"};
AudioFileSource* SampleStore::load(SampleGroup group, char* label)
{
	char fileName[40];
	sprintf(fileName, "%s-%s.mp3", suffixes[(int)group], label);
	return new AudioFileSourceSerialFlash(fileName);
}
AudioFileSource* SampleStore::load(SampleGroup group, const char* label)
{
	return SampleStore::load(group, (char*)label);
}
