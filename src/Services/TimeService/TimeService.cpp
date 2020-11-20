#include "TimeService.h"
#include <NTPClient.h>
#include <WiFi.h>
#include "../LocationService/LocationService.h"
#include <Util/Task.h>

TimeServiceImpl TimeService;

TimeServiceImpl::TimeServiceImpl() : timeClient(ntpUDP){
	fetchTask = new Task("TimeFetch", [](Task* task){
		if(!Net.checkConnection()){
			return;
		}

		TimeServiceImpl* instance = static_cast<TimeServiceImpl*>(task->arg);
		NTPClient& client = instance->timeClient;

		if(!client.forceUpdate()){
			Serial.println("Time fetch failed");
		}

		instance->setTime(client.getEpochTime());
		instance->fetching = false;
		instance->refreshMicros = 0;
	}, 2048, this);
}

void TimeServiceImpl::begin(){
	if(running) return;

	timeClient.begin();
	running = true;

	fetchTime();
}

void TimeServiceImpl::end(){
	if(!running) return;

	running = false;
	timeClient.end();
	ntpUDP.flush();
	ntpUDP.stop();
}

void TimeServiceImpl::setTime(uint unixTime){
	unixtime = unixTime;
	currentMillis = millis();
}

uint TimeServiceImpl::getTime(){
	uint diff = (millis() - currentMillis) / 1000;
	return (unixtime + LocationService.getLocation()->timezoneOffset + diff);
}

void TimeServiceImpl::fetchTime(){
	if(!running || fetching) return;
	fetching = true;
	fetchTask->start(0, 0);
}

void TimeServiceImpl::loop(uint _time){
	if(!running) return;

	refreshMicros += _time;
	if(refreshMicros > 300000000){ // 5 min, 300000000 us
		fetchTime();
	}
}

void TimeServiceImpl::state(wl_status_t status){
	if(status == WL_CONNECTED){
		begin();
	}else{
		end();
	}
}
