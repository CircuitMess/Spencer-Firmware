#include "LocationService.h"
#include <NTPClient.h>
#include <WiFi.h>

LocationServiceImpl LocationService;
bool LocationServiceImpl::fetchLocation()
{
	HTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	http.begin("http://ipinfo.io/geo");
	// http.addHeader("Content-Type", "application/json; charset=utf-8");
	// http.addHeader("Accept-Encoding", "identity");

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
	serializeJsonPretty(json, Serial);
	strcpy(data.IPaddress, json["ip"].as<const char*>());
	strcpy(data.city, json["city"].as<const char*>());
	strcpy(data.countryCode, json["country"].as<const char*>());
	strcpy(data.timezone, json["timezone"].as<const char*>());

	// data.IPaddress = json["ip"].as<const char*>();
	// data.city = json["city"].as<const char*>();
	// data.countryCode = json["country"].as<const char*>();
	// data.timezone = json["timezone"].as<const char*>();

	return true;
}

LocationData* LocationServiceImpl::getLocation()
{
	return &data;
}