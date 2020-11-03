#ifndef SPENCER_HTTPSERVER_H
#define SPENCER_HTTPSERVER_H

#include <WebServer.h>
#include <WiFi.h>
#include <loop/LoopListener.h>
#include <DNSServer.h>
class HTTPserver : public LoopListener
{
public:
	HTTPserver();
	void start();
	void stop();
	~HTTPserver();
	void loop(uint _time) override;
	
private:
	void sendContentFromFlash(const char* path);
	const char* host_ssid = "SpencerHotspot";
	IPAddress local_ip;
	IPAddress gateway;
	IPAddress subnet;
	WebServer server;

	static const char *index_html;
	static HTTPserver *instance;
};



#endif