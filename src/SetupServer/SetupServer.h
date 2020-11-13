#ifndef SPENCER_SETUPSERVER_H
#define SPENCER_SETUPSERVER_H

#include <WebServer.h>
#include <WiFi.h>
#include <Loop/LoopListener.h>
#include <DNSServer.h>
#include <Util/Task.h>

class SetupServer {
public:
	SetupServer();
	~SetupServer();

	void start();
	void stop();
	
private:
	static SetupServer *instance;

	Task task;
	static void taskFunc(Task* task);

	const char* SSID = "SpencerHotspot";

	const IPAddress spencerIP;
	WebServer server;
	DNSServer dnsServer;

	void registerHandlers();
};



#endif