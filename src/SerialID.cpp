#include <Loop/LoopManager.h>
#include "SerialID.h"
#include "Settings.h"

SerialIDImpl SerialID;

void SerialIDImpl::start(){
	LoopManager::addListener(this);
}

void SerialIDImpl::stop(){
	LoopManager::removeListener(this);
}

void SerialIDImpl::loop(uint micros){
	if(Serial.available()){
		char now = Serial.read();

		if(last == 'I' && now == 'D'){
			uint64_t mac = ESP.getEfuseMac();
			uint32_t upper = mac >> 32;
			uint32_t lower = mac & 0xffffffff;
			Serial.printf("Spencer:%u:%d:%x%x\n", Settings.getVersion(), Settings.get().calibrated, upper, lower);
		}

		last = now;
	}
}
