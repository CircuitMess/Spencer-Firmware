#include <Arduino.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <CircuitOS.h>
#include <Input/InputGPIO.h>
#include "src/Speech/SpeechToIntent.h"


InputGPIO input;
void setup(){
	Serial.begin(115200);

	SPIClass spi(3);
	spi.begin(18, 19, 23, 26);
	if(!SerialFlash.begin(spi, 26)){
		Serial.println("Flash fail");
		return;
	}
	// input.setBtnPressCallback(17, speechToIntent.identifyVoice())

}

void loop(){
}
