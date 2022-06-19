#include <Loop/LoopManager.h>
#include <WiFi.h>
#include "SerialSetup.h"
#include <Settings.h>
#include "../SerialID.h"

SerialSetup::SerialSetup() : scanTask("SetupScan", [](Task* task){
	SerialSetup* instance = static_cast<SerialSetup*>(task->arg);

	int n = WiFi.scanNetworks();
	for(int i = 0; i < n; i++){
		Serial.printf("SCN:%s\n", WiFi.SSID(i).c_str());
	}

	Serial.println("SCN:--SCN");

	if(task->running){
		instance->scanning = false;
	}
}, 2048, this){

}

void SerialSetup::loop(uint micros){
	if(!Serial.available()) return;

	cursor = (cursor + 1) % 3;
	sig[cursor] = Serial.read();

	Option option = getOption();
	if(option == NONE){
		return;
	}

	clearNL();

	switch(getOption()){
		case GET:
			printSettings();
			break;
		case SET:
			readSettings();
			break;
		case SCN:
			printScan();
			break;
		default:
			return;
	}
}

SerialSetup::Option SerialSetup::getOption(){
	if(checkOption("SET")){
		return SET;
	}else if(checkOption("GET")){
		return GET;
	}else if(checkOption("SCN")){
		return SCN;
	}
	return NONE;
}

bool SerialSetup::checkOption(const char* option){
	for(int i = 0; i < 3; i++){
		int c = (i + cursor + 1) % 3;
		if(sig[c] != option[i]) return false;
	}

	return true;
}

void SerialSetup::start(){
	SerialID.stop();
	LoopManager::addListener(this);
	Serial.println("SPENCER:SETTINGS");
}

void SerialSetup::stop(){
	scanTask.stop();
	LoopManager::removeListener(this);
	SerialID.start();
}

void SerialSetup::readSettings(){
	readIntoBuffer(Settings.get().SSID, 64);
	readIntoBuffer(Settings.get().pass, 64);

	char fahr[2];
	readIntoBuffer(fahr, 2);
	Settings.get().fahrenheit = fahr[0] == '1';

	Settings.store();

	Serial.println("OK");

	if(settingsSetCallback){
		settingsSetCallback();
	}
}

void SerialSetup::printSettings(){
	uint64_t mac = ESP.getEfuseMac();
	uint32_t upper = mac >> 32;
	uint32_t lower = mac & 0xffffffff;


	Serial.printf("SPENCER:%x%x:%u\n", upper, lower, Settings.getVersion());
	Serial.printf("SET:%s\n", Settings.get().SSID);
	Serial.printf("SET:%s\n", Settings.get().pass);
	Serial.printf("SET:%d\n", Settings.get().fahrenheit);
	Serial.println("SET:--SET");
}

void SerialSetup::printScan(){
	if(scanning) return;
	scanning = true;
	scanTask.start(1, 0);
}

void SerialSetup::readIntoBuffer(char* buffer, int limit){
	int cursor = 0;

	do {
		while(!Serial.available()) delay(1);
		if(Serial.peek() == '\n' || Serial.peek() == '\r') break;
		buffer[cursor++] = Serial.read();
	} while(cursor < limit);

	if(cursor == limit) cursor--;
	buffer[cursor] = '\0';

	clearNL();
}

void SerialSetup::clearNL(){
	while(Serial.available() && (Serial.peek() == '\n' || Serial.peek() == '\r')){
		Serial.read();
	}
}

void SerialSetup::setSettingsSetCallback(void (* connectCallback)()){
	SerialSetup::settingsSetCallback = connectCallback;
}
