#include "SetupServer.h"
#include <WiFi.h>
#include <Loop/LoopManager.h>
#include <SerialFlash.h>
#include "../Settings.h"
#include "SetupRequestHandler.h"

SetupServer* SetupServer::instance = nullptr;

SetupServer::SetupServer() : spencerIP(8, 8, 4, 4), server(80){
	instance = this;
}

SetupServer::~SetupServer(){
	instance = nullptr;
}

void SetupServer::start(){
	WiFi.mode(WIFI_AP_STA);
	delay(2000);
	WiFi.softAP(SSID, "");
	WiFi.softAPConfig(spencerIP, spencerIP, IPAddress(255, 255, 255, 0));

	dnsServer.start(53, "*", spencerIP);

	registerHandlers();

	server.begin();

	LoopManager::addListener(this);
}

void SetupServer::stop(){
	server.stop();
	dnsServer.stop();
	delay(500);
	WiFi.softAPdisconnect();

	LoopManager::removeListener(this);
}

void SetupServer::loop(uint _time){
	dnsServer.processNextRequest();
	server.handleClient();
}

#define ARR_SIZEOF(x) (sizeof(x) / sizeof(x[0]))

void SetupServer::registerHandlers(){
	server.addHandler(new SetupRequestHandler());

	server.on("/scan", HTTP_POST, [](){
		if(instance == nullptr) return;

		int n = WiFi.scanNetworks();
		String content = "";
		for(int i = 0; i < n; i++){
			content += WiFi.SSID(i);

			if(i != n-1){
				content += "\n";
			}
		}

		instance->server.send(200, "text/plain", content);
	});

	server.on("/get", HTTP_POST, [](){
		if(instance == nullptr) return;

		String content = "";

		content += Settings.get().SSID; content += '\n';
		content += Settings.get().pass; content += '\n';
		content += Settings.get().TTS_key; content += '\n';
		content += Settings.get().STT_key;

		instance->server.send(200, "text/plain", content);
	});

	server.on("/save", HTTP_POST, [](){
		if(instance == nullptr) return;

		if(instance->server.args() != 4){
			instance->server.send(200, "text/html", "err");
			return;
		}

		instance->server.arg(0).toCharArray(Settings.get().SSID, ARR_SIZEOF(SettingsData::SSID));
		instance->server.arg(1).toCharArray(Settings.get().pass, ARR_SIZEOF(SettingsData::pass));
		instance->server.arg(2).toCharArray(Settings.get().TTS_key, ARR_SIZEOF(SettingsData::TTS_key));
		instance->server.arg(3).toCharArray(Settings.get().STT_key, ARR_SIZEOF(SettingsData::STT_key));
		Settings.store();

		instance->server.send(200, "text/html", "ok");
	});
}
