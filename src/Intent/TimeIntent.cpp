#include "TimeIntent.h"
#include "../Services/TimeService/TimeService.h"
#include "../Services/Audio/Audio.h"
TimeIntent::TimeIntent(void* params) : Intent(params)
{
 	//start loading animation

	//make prepared statement
	TimeIntentParam _params = *static_cast<TimeIntentParam*>(params);
	DateTime now = DateTime(_params.unixTime);
	// Serial.printf("%d:%d:%d\n", now.hour(), now.minute(), now.second());
	char buff[4] = {0};
	speakFile = new CompositeAudioFileSource();

	AudioFileSource* test = SampleStore::load(SampleGroup::Generic, "HELLO");
	// AudioFileSource* test = new AudioFileSourceSerialFlash("generic-HELLO.mp3");
	test->seek(0,SEEK_SET);
	// speakFile->add(test);
	// speakFile->add((AudioFileSource*)(new AudioFileSourceSerialFlash("generic-HELLO.mp3")));
	Serial.println("here");
	delay(5);
	switch (_params.type)
	{
	case TimeIntentType::TIME:
		//parsing time to speech
		// speakFile->add(new AudioFileSourceSerialFlash("time-The_time_is.mp3"));
		
		speakFile->add(SampleStore::load(SampleGroup::Time, "The_time_is"));
		Serial.println("here");
		delay(5);
		sprintf(buff, "%d", now.hour() > 12 ? now.hour() - 12 : now.hour());
		Serial.println("here");
		delay(5);
		speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
		Serial.println("here");
		delay(5);
		if(now.minute() > 19)
		{
			sprintf(buff, "%d", now.minute() / 10);
			speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
			if(now.minute()%10 > 0)
			{
				sprintf(buff, "%d", now.minute() % 10);
				speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
			}
		}
		else
		{
			if(now.minute() < 10)
			{
				speakFile->add(SampleStore::load(SampleGroup::Numbers, "0"));
			}

			sprintf(buff, "%d", now.minute());
			speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
		}
		speakFile->add(SampleStore::load(SampleGroup::Time, now.hour() > 12 ? "PM" : "AM"));
		break;
	
	case TimeIntentType::DATE:
		speakFile->add(SampleStore::load(SampleGroup::Time, "It's_the"));
		if(now.day() > 19)
		{
			if(now.day()%10 > 0)
			{
				sprintf(buff, "%d", now.day() / 10);
				speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
				sprintf(buff, "%d.", now.day() % 10);
				speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
			}
			else
			{
				sprintf(buff, "%d.", now.day());
				speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
			}
		}
		else
		{
			sprintf(buff, "%d.", now.day());
			speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
		}
		speakFile->add(SampleStore::load(SampleGroup::Time, "of"));
		sprintf(buff, "%d", now.month());
		speakFile->add(SampleStore::load(SampleGroup::Months, buff));

		for(uint8_t i = 0; i < 2; i++)
		{
			uint8_t temp = 0;
			if(i == 0)
				temp = int(now.year() / 100);
			else
				temp = now.year()%100;
			if(temp > 19)
			{
				sprintf(buff, "%d", temp / 10);
				speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
				if(temp % 10 > 0)
				{
					sprintf(buff, "%d", temp % 10);
					speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
				}
			}
			else
			{
				if(temp < 10)
				{
					speakFile->add(SampleStore::load(SampleGroup::Time, "0"));
				}
				sprintf(buff, "%d", temp);
				speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
			}
		}
		break;
	default:
		break;
	}
	Serial.println("playing file");
	delay(5);
	Audio.playMP3(speakFile);
}

TimeIntent::~TimeIntent()
{
}

void TimeIntent::loop()
{
	
}