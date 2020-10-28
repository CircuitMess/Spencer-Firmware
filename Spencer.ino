#include <Arduino.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <CircuitOS.h>
#include <Input/InputGPIO.h>
#include "src/Speech/SpeechToIntent.h"
#include "src/Services/Audio/Audio.h"
#include "Spencer.hpp"
#include "src/LEDmatrix/LEDmatrix.h"
#include "src/State/State.h"
#include "src/State/IdleState.h"
#include "src/Util/FlashTools.h"
#include "src/Intent/IntentStore.h"
#include <Loop/LoopManager.h>
#include <WiFi.h>
#include "src/Services/TimeService/TimeService.h"
#include "src/Intent/TimeIntent.h"


void setup(){
	Serial.begin(115200);

	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	if(!SerialFlash.begin(spi, FLASH_CS_PIN)){
		Serial.println("Flash fail");
		return;
	}

	WiFi.begin("CircuitMess", "MAKERphone!");
	while(WiFi.status() != WL_CONNECTED);

	if(!LEDmatrix.begin()){
		Serial.println("couldn't start matrix");
		for(;;);
	}
	LEDmatrix.clear();
	LEDmatrix.setBrightness(20);
	LEDmatrix.setRotation(2);

	Audio.begin();
	IntentStore::fillStorage();

	LoopManager::addListener(&Audio);
	LoopManager::addListener(&LEDmatrix);
	LoopManager::addListener(&TimeService);
	LoopManager::addListener(new InputGPIO());

	State::changeState(new IdleState());
}

void loop(){
	LoopManager::loop();
}

