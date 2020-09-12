#include <Arduino.h>
#include <SPI.h>
#include "src/Services/Audio/Audio.h"

#include "Spencer.hpp"
#include <CircuitOS.h>
#include <Input/InputGPIO.h>

InputGPIO input;

Audio audio;

void spaces(int num) {
  for (int i=0; i < num; i++) {
    Serial.print(" ");
  }
}

void setup(){
	Serial.begin(115200);

	
	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	if(!SerialFlash.begin(spi, FLASH_CS_PIN))
	{
		Serial.println("flash error");
	}
	// Serial.println("erasing");
	// SerialFlash.eraseAll();
	while (!SerialFlash.ready());
	Serial.println("ready");

	
	audio.begin();
	input.setBtnPressCallback(17, [](){
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