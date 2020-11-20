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

void NetImpl::setState(wl_status_t state){
	if(this->state != state){
		this->state = state;

		for(const auto& listener : stateListeners){
			listener->state(state);
		}

		for(const auto& callback : stateCallbacks){
			callback(state);
		}
	}
}

void NetImpl::connect(){
	LEDmatrix.startAnimation(new Animation("GIF-wifi.gif"), true);

	state = WL_DISCONNECTED;

	LoopManager::addListener(this);

	connectRetries = 0;
	connecting = true;
	tryConnect();
}

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

		setState(WL_DISCONNECTED);

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
		// WiFi can get messed up sometimes, so retry if failed after only one try
		if(status != WL_CONNECTED && connectRetries == 0){
			retryConnect();
			return;
		}

		// done connecting, process result
		connecting = false;
		LoopManager::removeListener(this);

		setState(status);
	}
}

void NetImpl::addStateCallback(NetStateCallback* callback){
	stateCallbacks.push_back(callback);
}

void NetImpl::addStateListener(NetStateListener* listener){
	stateListeners.push_back(listener);
}

bool NetImpl::checkConnection(){
	if(WiFi.status() != WL_CONNECTED){
		setState(WL_DISCONNECTED);
		return false;
	}

	HTTPClient client;
	client.setConnectTimeout(2000);
	client.useHTTP10(true);
	client.setReuse(false);

	if(!client.begin("http://spencer.circuitmess.com:7979/index")){
		client.end();
		client.getStream().flush();
		setState(WL_DISCONNECTED);
		return false;
	}

	client.setUserAgent("Spencer");

	int code = client.GET();
	if(code != 200){
		client.end();
		client.getStream().flush();
		setState(WL_DISCONNECTED);
		return false;
	}

	String data = client.getString();
	client.end();
	client.getStream().flush();

	if(data.substring(0, 2) != "OK"){
		setState(WL_DISCONNECTED);
		return false;
	}

	setState(WL_CONNECTED);
	return true;
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

	setState(WiFi.status());
	return state == WL_CONNECTED;
}