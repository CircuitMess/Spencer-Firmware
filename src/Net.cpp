#include <WiFi.h>
#include <Loop/LoopManager.h>
#include <HTTPClient.h>
#include "LEDmatrix/LEDmatrix.h"
#include "Net.h"

NetImpl Net;

NetImpl::NetImpl(){
	WiFi.enableSTA(true);
}

void NetImpl::set(const char* ssid, const char* pass){
	this->ssid = ssid;
	this->pass = pass;
}

void NetImpl::connect(){
	LEDmatrix.startAnimation(new Animation("GIF-wifi.gif"), true);

	LoopManager::addListener(this);

	connectRetries = 0;
	connecting = true;
	tryConnect();
}

// status() || status() >= WL_DISCONNECTED

void NetImpl::tryConnect(){
	WiFi.disconnect(true);
	WiFi.persistent(false);
	WiFi.begin(ssid, pass);
	WiFi.setSleep(false);

	connectTime = millis();
}

void NetImpl::retryConnect(){
	if(++connectRetries == 3){
		connecting = false;

		if(statusCallback){
			statusCallback(WL_DISCONNECTED);
		}

		LoopManager::removeListener(this);
		return;
	}

	tryConnect();
}

void NetImpl::loop(uint micros){
	if(!connecting) return;

	wl_status_t status = WiFi.status();

	if(!status || status >= WL_DISCONNECTED){
		// still connecting
		if(millis() - connectTime >= 5000){ // 5 sec timeout
			retryConnect();
		}
	}else{
		if(status != WL_CONNECTED && connectRetries == 0){
			// WiFi can get messed up sometimes, so retry if failed after only one try
			retryConnect();
			return;
		}

		// done connecting, process result
		connecting = false;
		LoopManager::removeListener(this);

		if(statusCallback){
			statusCallback(status);
		}
	}
}

void NetImpl::setStatusCallback(void (* statusCallback)(wl_status_t)){
	NetImpl::statusCallback = statusCallback;
}

bool NetImpl::checkConnection(){
	if(WiFi.status() != WL_CONNECTED) return false;

	HTTPClient client;
	client.setConnectTimeout(2000);
	client.useHTTP10(true);
	client.setReuse(false);

	if(!client.begin("http://spencer.circuitmess.com:7979/index")){
		client.end();
		client.getStream().flush();
		return false;
	}

	client.setUserAgent("Spencer");

	int code = client.GET();
	if(code != 200){
		client.end();
		client.getStream().flush();
		return false;
	}

	String data = client.getString();
	client.end();
	client.getStream().flush();

	return data.substring(0, 2) == "OK";
}

bool NetImpl::reconnect(){
	int retries = 0;

	while(WiFi.status() != WL_CONNECTED && retries++ < 2){
		tryConnect();

		while(WiFi.status() != WL_CONNECTED){
			delay(500);
			if(millis() - connectTime >= 5000) break;
		}

	}

	return WiFi.status() == WL_CONNECTED;
}