#include "SampleStore.h"
#include "AudioFileSourceSerialFlash.h"
AudioFileSource* SampleStore::load(SampleGroup group, char* label)
{
	char fileName[40];
	char suffix;
	switch (group)
	{
	case SampleGroup::Months:
		suffix = 'm';
		break;
	case SampleGroup::Numbers:
		suffix = 'n';
		break;
	case SampleGroup::Jokes:
		suffix = 'j';
		break;
	case SampleGroup::Generic:
		suffix = 'g';
		break;
	default:
		suffix = 'g';
		break;
	}
	sprintf(fileName, "%s-%c.mp3", label, suffix);
	return new AudioFileSourceSerialFlash(fileName);
}