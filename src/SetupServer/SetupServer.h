#ifndef SPENCER_SETUPSERVER_H
#define SPENCER_SETUPSERVER_H

#include <WebServer.h>
#include <WiFi.h>
#include <Loop/LoopListener.h>
#include <DNSServer.h>

class SetupServer : public LoopListener
{
public:
	SetupServer();
	~SetupServer();
	void loop(uint _time) override;
	
private:
	static SetupServer *instance;

	const char* SSID = "SpencerHotspot";

	const IPAddress spencerIP;
	WebServer server;
	DNSServer dnsServer;

	void registerHandlers();
};



#endif