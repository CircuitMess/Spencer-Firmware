#include "SetupServer.h"
#include <WiFi.h>
#include <Loop/LoopManager.h>
#include <SerialFlash.h>
#include <esp_wifi.h>
#include <Settings.h>
#include "SetupRequestHandler.h"

SetupServer* SetupServer::instance = nullptr;

SetupServer::SetupServer() : spencerIP(10, 0, 0, 1), server(80){
	instance = this;

	Serial.printf("WiFi task pinned to core %d\n", WIFI_TASK_CORE_ID);

	delay(2000);
	esp_wifi_set_ps(WIFI_PS_NONE);
	WiFi.softAP(SSID, "");
	WiFi.softAPConfig(spencerIP, spencerIP, IPAddress(255, 255, 255, 0));

	dnsServer.start(53, "setup.circuitmess.com", spencerIP);

	registerHandlers();
}

SetupServer::~SetupServer(){dnsServer.stop();
	delay(500);
	WiFi.softAPdisconnect();

	instance = nullptr;
}

void SetupServer::start(){
	server.begin();
	LoopManager::addListener(this);
}

void SetupServer::stop(){
	LoopManager::removeListener(this);
	server.stop();
}

void SetupServer::loop(uint micros){
	dnsServer.processNextRequest();
	server.handleClient();
	vTaskDelay(1);
}

#define ARR_SIZEOF(x) (sizeof(x) / sizeof(x[0]))

void SetupServer::registerHandlers(){
	server.addHandler(new SetupRequestHandler());

	server.on("/scan", HTTP_POST, [](){
		if(instance == nullptr) return;

		instance->scan();

		instance->server.send(200, "text/plain", instance->scanned);
	});

	server.on("/get", HTTP_POST, [](){
		if(instance == nullptr) return;

		String content = "";

		content += Settings.get().SSID; content += '\n';
		content += Settings.get().pass;

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
		Settings.store();

		instance->server.send(200, "text/html", "ok");
	});
}

void SetupServer::scan(){
	if(scanning) return;

	scanning = true;
	int n = WiFi.scanNetworks();
	String scanned = "";
	for(int i = 0; i < n; i++){
		scanned += WiFi.SSID(i);

		if(i != n-1){
			scanned += "\n";
		}
	}

	this->scanned = scanned;
	scanning = false;
}
