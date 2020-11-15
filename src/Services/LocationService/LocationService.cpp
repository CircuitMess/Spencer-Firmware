#include "LocationService.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <string>
#define CA "EB:6D:04:1A:C9:07:50:C7:52:C5:BC:69:E0:79:87:A6:5A:E5:2F:A8:23:D7:93:52:8C:9F:E8:62:27:AB:65:47"

LocationServiceImpl LocationService;
bool LocationServiceImpl::fetchLocation()
{
	//location info request
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	http.begin("http://ipinfo.io/geo");

	int httpCode = http.GET();
	if (httpCode != HTTP_CODE_OK) {
		return false;
	}

	const int SIZE = JSON_OBJECT_SIZE(8) + 170;
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, http.getStream());

	http.end();
	http.getStream().stop();
	http.getStream().flush();

	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		return false;
	}

	if(!json.containsKey("country")){
		Serial.println("Failed recognizing");
		return false;
	}
	strcpy(data.IPaddress, json["ip"].as<const char*>());
	strcpy(data.city, json["city"].as<const char*>());
	strcpy(data.countryCode, json["country"].as<const char*>());
	strcpy(data.timezone, json["timezone"].as<const char*>());
	//"loc": "45.8144,15.9780"
	std::string loc = json["loc"];
	size_t pos = loc.find(",");
	std::string str3 = loc.substr(pos + 1);
	data.lat = atof(loc.substr(0, pos-1).c_str());
	data.lon = atof(loc.substr(pos + 1).c_str());
	//timezone offset request
	HTTPClient http2;
	http2.begin("https://spencer.circuitmess.com:8443/timezone", CA);
	http2.addHeader("Zone", data.timezone);
	httpCode = http2.GET();
	if (httpCode != HTTP_CODE_OK) {
		return false;
	}
	char offset[12];
	http2.getStream().readBytes(offset, 12);
	offset[11] = '\0';
	data.timezoneOffset = atoi(offset) / 1000;
	http2.end();
	http2.getStream().stop();
	http2.getStream().flush();

	return true;
}

LocationData* LocationServiceImpl::getLocation()
{
	return &data;
}