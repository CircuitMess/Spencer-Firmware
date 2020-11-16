#ifndef SPENCER_SETUPSERVER_H
#define SPENCER_SETUPSERVER_H

#include <WebServer.h>
#include <WiFi.h>
#include <Loop/LoopListener.h>
#include <DNSServer.h>
#include <Util/Task.h>

class SetupServer : public LoopListener {
public:
	SetupServer();
	~SetupServer();

	void start();
	void stop();
	void loop(uint micros) override;

private:
	static SetupServer *instance;

	const char* SSID = "SpencerHotspot";

	const IPAddress spencerIP;
	WebServer server;
	DNSServer dnsServer;

	void scan();

	bool scanning = false;
	String scanned = "";

	void registerHandlers();
};



#endif