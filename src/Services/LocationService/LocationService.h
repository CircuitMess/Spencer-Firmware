#ifndef SPENCER_LOCATIONSERVICE_H
#define SPENCER_LOCATIONSERVICE_H

#include <HTTPClient.h>
#include <ArduinoJson.h>
struct LocationData
{
	char IPaddress[16];
	char city[30];
	char countryCode[3];
	char timezone[30];
};

class LocationServiceImpl
{
public:
	LocationData* getLocation();
	//using ipinfo.io by default
	bool fetchLocation();
private:
	LocationData data;
};
extern LocationServiceImpl LocationService;

#endif