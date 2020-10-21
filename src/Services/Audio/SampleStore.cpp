#include "SampleStore.h"
#include "AudioFileSourceSerialFlash.h"
AudioFileSource* SampleStore::load(SampleGroup group, char* label)
{
	char fileName[40] = {0};

	const char *suffix = new char[20];
	switch (group)
	{
	case SampleGroup::Months:
		suffix = "months";
		break;
	case SampleGroup::Numbers:
		suffix = "numbers";
		break;
	case SampleGroup::Jokes:
		suffix = "jokes";
		break;
	case SampleGroup::Generic:
		suffix = "generic";
		break;
	case SampleGroup::Time:
		suffix = "time";
		break;
	default:
		suffix = "\0";
		break;
	}
	if(strcmp(suffix, "\0") != 0)
	{
		sprintf(fileName, "%s-%s.mp3", suffix, label);
	}
	else
	{
		sprintf(fileName, "%s.mp3", label);
	}
	
	return new AudioFileSourceSerialFlash(fileName);
}
AudioFileSource* SampleStore::load(SampleGroup group, const char* label)
{
	SampleStore::load(group, (char*)label);
}
