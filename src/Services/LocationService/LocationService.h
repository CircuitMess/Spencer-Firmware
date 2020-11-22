#ifndef SPENCER_LOCATIONSERVICE_H
#define SPENCER_LOCATIONSERVICE_H

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Util/Task.h>
#include <Loop/LoopListener.h>

struct LocationData
{
	char IPaddress[16];
	char city[30];
	char countryCode[3];
	char timezone[30];
	int timezoneOffset = 0; //in seconds!
	float lat;
	float lon;
};

class LocationServiceImpl : public LoopListener
{
public:
	LocationServiceImpl();
	LocationData* getLocation();
	//using ipinfo.io by default
	void fetchLocation();

	bool isSet() const;

	void loop(uint micros) override;

private:
	LocationData data;
	bool set = false;

	uint8_t retries = 0;
	bool fetching = false;
	Task fetchTask;
};
extern LocationServiceImpl LocationService;

#endif