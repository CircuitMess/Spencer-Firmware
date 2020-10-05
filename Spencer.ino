#include <Arduino.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <CircuitOS.h>
#include <Input/InputGPIO.h>
#include "src/Services/Audio/Audio.h"
#include "Spencer.hpp"
#include "src/LEDmatrix/LEDmatrix.h"
#include <Loop/LoopManager.h>

InputGPIO input;
Audio audio;
LEDmatrix ledmatrix;
void setup(){
	Serial.begin(115200);

	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	if(!SerialFlash.begin(spi, FLASH_CS_PIN)){
		Serial.println("Flash fail");
		return;
	}

	if(!ledmatrix.begin())
	{
		Serial.println("couldn't start matrix");
		while(1);
	}
	ledmatrix.clear();
	ledmatrix.setBrightness(20);
	ledmatrix.setRotation(2);

	ledmatrix.startAnimation(new Animation("wifi.gif"), 1);
	LoopManager::addListener(&ledmatrix);
}

void loop(){
	LoopManager::loop();
	ledmatrix.push();
}