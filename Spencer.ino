#include <Arduino.h>
#include <SPI.h>
#include <SerialFlash.h>

void setup(){
	Serial.begin(115200);

	SPIClass spi(3);
	spi.begin(18, 19, 23, 26);
	if(!SerialFlash.begin(spi, 26)){
		Serial.println("Flash fail");
		return;
	}
}

void loop(){
	input.loop(0);
	audio.loop();
}