#ifndef SPENCER_LIMITTRACKINGSERVICE_H
#define SPENCER_LIMITTRACKINGSERVICE_H

#include <Loop/LoopListener.h>
#define STT_MAX_SECONDS 3600
#define TTS_MAX_CHARS 4000000

class LimitTrackingServiceImpl : public LoopListener
{
public:
	LimitTrackingServiceImpl();
	~LimitTrackingServiceImpl();
	
	void begin();
	void end();

	float getSTTusage(); // in percentage
	float getTTSusage(); // in percentage

	void addSTTusage(uint32_t audioLength);
	void addTTSusage(uint32_t charactersCount);

	void loop(uint _time) override;

private:
	uint32_t startingTime = 0;
	uint32_t currentSTTseconds = 0;
	uint32_t currentTTSchars = 0;

	uint32_t dailyWarningResetTime = 0;
};

extern LimitTrackingServiceImpl LimitTrackingService;

#endif