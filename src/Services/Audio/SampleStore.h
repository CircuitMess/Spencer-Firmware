#ifndef SPENCER_SAMPLESTORE_H
#define SPENCER_SAMPLESTORE_H
#include <AudioFileSource.h>

enum SampleGroup{
	Months, Numbers, Jokes, Generic, Time, Special
};

class SampleStore
{
public:

	static AudioFileSource* load(SampleGroup group, const char* label);
};

#endif