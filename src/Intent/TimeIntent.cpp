#include "TimeIntent.h"
#include "../Services/TimeService/TimeService.h"
#include "../Services/Audio/Audio.h"
#include "../LEDmatrix/LEDmatrix.h"

TimeIntent::TimeIntent(void* params)
{
 	//start loading animation

	//make prepared statement
	_params = *static_cast<TimeIntentParam*>(params);
	DateTime now = DateTime(_params.unixTime);
	// Serial.printf("%d:%d:%d\n", now.hour(), now.minute(), now.second());
	char buff[4] = {0};
	speakFile = new CompositeAudioFileSource();
	switch (_params.type)
	{
	case TimeIntentType::TIME:
		//parsing time to speech
		speakFile->add(SampleStore::load(SampleGroup::Time, "The_time_is"));
		sprintf(buff, "%d", now.hour() > 12 ? now.hour() - 12 : now.hour());
		speakFile->add(SampleStore::load(SampleGroup::Numbers, buff));
		if(now.minute() > 19)
		{
			sprintf(buff, "%d", (now.minute() / 10)*10);
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
				sprintf(buff, "%d", (now.day() / 10)*10);
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
				sprintf(buff, "%d", (temp / 10)*10);
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

	if(_params.type == TimeIntentType::TIME)
	{
		LEDmatrix.clear();
		if(now.hour()/10 + '0' != '1'){
			LEDmatrix.drawChar(0,7,now.hour()/10 + '0', 255, 0);
		}else{
			LEDmatrix.drawChar(1,7,now.hour()/10 + '0', 255, 0);
		}
		LEDmatrix.drawChar(4,7,(now.hour()%10) + '0', 255, 0);
		LEDmatrix.drawChar(9,7,now.minute()/10 + '0', 255, 0);
		if(now.minute()/10 == 1){
			LEDmatrix.drawChar(12,7,(now.minute()%10) + '0', 255, 0);
		}else{
			LEDmatrix.drawChar(13,7,(now.minute()%10) + '0', 255, 0);
		}
	}else{
		strncpy(scrollingText, "DD.MMM", 8);
		now.toString(scrollingText);
		textCursor = 15;
		elapsedMillis = millis();
	}
	Audio.playMP3(speakFile);
}

TimeIntent::~TimeIntent()
{
}

void TimeIntent::loop(uint micros)
{
	if(_params.type == TimeIntentType::TIME)
	{
		if(!Audio.isRunning() && !audioStopped)
		{
			audioStopped = 1;
			elapsedMillis = millis();
		}
		if(millis() - elapsedMillis > 3000 && audioStopped)
		{
			LEDmatrix.clear();
			//end
		}
	}else{
		if(textCursor > -45){
			if(millis() - elapsedMillis > 150)
			{
				textCursor--;
				elapsedMillis = millis();
			}
			LEDmatrix.clear();
			LEDmatrix.drawString(textCursor, 1, scrollingText);
		}else{
			LEDmatrix.clear();
			//end
		}
	}
}