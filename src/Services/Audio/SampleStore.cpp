#include "SampleStore.h"
#include "AudioFileSourceSerialFlash.h"
const char *prefixes[8] = {"months", "numbers", "jokes", "generic", "time", "special", "weather", "weekdays"};
AudioFileSource* SampleStore::load(SampleGroup group, const char* label)
{
	char fileName[40];
	sprintf(fileName, "%s-%s.mp3", prefixes[(int) group], label);
	return new AudioFileSourceSerialFlash(fileName);
}
