#include "SerialSetup.h"
#include "../Settings.h"
#include "../Net.h"

void SerialSetup::loop(uint micros){
	if(!Serial.available()) return;

	cursor = (cursor + 1) % 3;
	sig[cursor] = Serial.read();

	const char* check = "SET";
	for(int i = 0; i < 3; i++){
		int c = (i + cursor + 1) % 3;
		if(sig[c] != check[i]) return;
	}

	clearNL();
	readSettings();
	Serial.println("OK");

	if(settingsSetCallback){
		settingsSetCallback();
	}
}

void SerialSetup::readSettings(){
	readIntoBuffer(Settings.get().SSID, 64);
	readIntoBuffer(Settings.get().pass, 64);
	readIntoBuffer(Settings.get().TTS_key, 40);
	readIntoBuffer(Settings.get().STT_key, 40);

	Settings.store();
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
