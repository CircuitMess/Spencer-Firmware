#include <WiFi.h>
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
	connectRetries = 0;
	connecting = true;
	tryConnect();
}

// status() || status() >= WL_DISCONNECTED

void NetImpl::tryConnect(){
	WiFi.disconnect(true, true);
	WiFi.enableSTA(true);
	WiFi.begin(ssid, pass);

	connectTime = millis();
}

void NetImpl::retryConnect(){
	if(++connectRetries == 3){
		connecting = false;

		if(statusCallback){
			statusCallback(WL_DISCONNECTED);
		}

		return;
	}

	tryConnect();
}

void NetImpl::loop(uint micros){
	if(connecting){
		wl_status_t status = WiFi.status();

		if(!status || status >= WL_DISCONNECTED){
			// still connecting
			if(millis() - connectTime >= 10000){ // 10 sec timeout
				retryConnect();
			}
		}else{
			// done connecting, process result
			connecting = false;

			if(statusCallback){
				statusCallback(status);
			}
		}
	}
}

void NetImpl::setStatusCallback(void (* statusCallback)(wl_status_t)){
	NetImpl::statusCallback = statusCallback;
}
