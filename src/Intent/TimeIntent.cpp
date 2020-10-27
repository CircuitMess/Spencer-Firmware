#include "TimeIntent.h"
#include "../Services/TimeService/TimeService.h"
#include "../Services/Audio/Audio.h"
TimeIntent::TimeIntent(void* params)
{
	//start loading animation
	//make prepared statement
	TimeIntentParam _params = *static_cast<TimeIntentParam*>(params);
	DateTime now = DateTime(_params.unixTime);
	// Serial.printf("%d:%d:%d\n", now.hour(), now.minute(), now.second());
	char buff[4] = {0};
	speakFile = new CompositeAudioFileSource();
	switch (_params.type)
	{
	case TimeIntentType::TIME:
		//parsing time to speech
		
		speakFile->add(SampleStore::load(SampleGroup::Generic, "The time is"));
		sprintf(buff, "%d", now.hour() > 12 ? now.hour() - 12 : now.hour());
		speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
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
				speakFile->add(SampleStore::load(SampleGroup::Generic, "oh"));
			}

			sprintf(buff, "%d", now.minute());
			speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
		}
		speakFile->add(SampleStore::load(SampleGroup::Generic, now.hour() > 12 ? "PM" : "AM"));
		break;
	
	case TimeIntentType::DATE:
		speakFile->add(SampleStore::load(SampleGroup::Generic, "It's the"));
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
		speakFile->add(SampleStore::load(SampleGroup::Generic, "of"));
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
					speakFile->add(SampleStore::load(SampleGroup::Generic, "oh"));
				}
				sprintf(buff, "%d", temp);
				speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
			}
		}
		break;
	default:
		break;
	}
	audio.playMP3(speakFile);
}

TimeIntent::~TimeIntent()
{
}

void TimeIntent::loop()
{
	
}