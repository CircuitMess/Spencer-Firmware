#include <Arduino.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <CircuitOS.h>
#include <Input/InputGPIO.h>
#include "src/Services/Audio/Audio.h"
#include "Spencer.hpp"
InputGPIO input;
Audio audio;
void setup(){
	Serial.begin(115200);

	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	if(!SerialFlash.begin(spi, FLASH_CS_PIN)){
		Serial.println("Flash fail");
		return;
	}
	
	Serial.println("erasing");
	SerialFlash.eraseAll();
	while (!SerialFlash.ready());
	Serial.println("ready");

	audio.begin();
	input.setBtnPressCallback(BTN_PIN, [](){
		// audio.begin();
		Serial.println("start recording!");
		audio.record([](){
			Serial.println("record done");
			audio.play("recording.wav");
		});
	});
}

void loop(){
	input.loop(0);
	audio.loop();
}
