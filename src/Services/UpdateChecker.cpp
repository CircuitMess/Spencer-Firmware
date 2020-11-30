#include <HTTPClient.h>
#include "UpdateChecker.h"
#include <Net/Net.h>
#include <Settings.h>

UpdateCheckerImpl UpdateChecker;

UpdateCheckerImpl::UpdateCheckerImpl() : checkTask("UpdateCheck", [](Task* task){
	UpdateCheckerImpl* instance = static_cast<UpdateCheckerImpl*>(task->arg);

	if(!Net.checkConnection()){
		instance->checking = false;
		return;
	}

	HTTPClient client;
	client.setConnectTimeout(2000);
	client.useHTTP10(true);
	client.setReuse(false);

	if(!client.begin("http://spencer.circuitmess.com:7979/version")){
		client.end();
		client.getStream().flush();
		instance->checking = false;
		return;
	}

	client.setUserAgent("Spencer");

	int code = client.GET();
	if(code != 200){
		client.end();
		client.getStream().flush();
		instance->checking = false;
		return;
	}

	String data = client.getString();
	client.end();
	client.getStream().flush();

	if(data.length() == 0){
		instance->checking = false;
		return;
	}

	uint version = 0;
	for(int i = 0; i < 3; i++){
		if(data.length() < i) break;
		if(data.charAt(i) < '0' || data.charAt(i) > '9'){
			break;
		}
		version = version * 10 + data.charAt(i) - '0';
	}

	if(version == 0){
		instance->checking = false;
		return;
	}

	instance->version = version;
	instance->checking = false;
}, 4096, this){

	notifiedVersion = Settings.getVersion();
}

void UpdateCheckerImpl::loop(uint micros){
	if(!running) return;
	if(millis() - checkTime > 5 * 60 * 1000){
		checkVersion();
		checkTime = millis();
	}
}

bool UpdateCheckerImpl::updateAvailable(){
	return version > Settings.getVersion();
}

void UpdateCheckerImpl::checkVersion(){
	if(checking || !running) return;
	checking = true;
	checkTask.start(0, 0);
}

void UpdateCheckerImpl::state(wl_status_t status){
	if(status == WL_CONNECTED){
		running = true;
		checkVersion();
	}else{
		running = false;
	}
}

bool UpdateCheckerImpl::hasNotified(){
	return notifiedVersion == version;
}

void UpdateCheckerImpl::notify(){
	notifiedVersion = version;
}
