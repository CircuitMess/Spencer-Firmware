#include <Arduino.h>
#include <Spencer.hpp>
#include "src/State/State.h"
#include <Util/FlashTools.h>
#include "src/State/IdleState.h"
#include "src/Intent/IntentStore.h"
#include "src/Services/TimeService/TimeService.h"
#include "src/Intent/TimeIntent.h"
#include "src/SerialID.h"
#include "src/Services/SerialSetup.h"
#include "src/State/StartupState.h"
#include "src/Services/UpdateChecker.h"
#include "src/HardwareTest.h"


bool checkJig(){
	if(Settings.get().calibrated) return false;

	pinMode(22, OUTPUT);
	pinMode(21, INPUT_PULLDOWN);

	digitalWrite(22, HIGH);
	delay(10);
	if(digitalRead(21) != HIGH) return false;

	digitalWrite(22, LOW);
	delay(10);
	if(digitalRead(21) != LOW) return false;

	return true;
}

void setup(){
	Serial.begin(115200);

	disableCore0WDT();
	disableCore1WDT();

	if(checkJig()){
		HardwareTest test;
		test.start();
		for(;;);
	}

	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	SerialFlash.setSettings(SPISettings(30000000, MSBFIRST, SPI_MODE0));
	if(!SerialFlash.begin(spi, FLASH_CS_PIN)){
		Serial.println("Flash fail");
		return;
	}

	if(!LEDmatrix.begin()){
		Settings.begin();
		for(;;){
			SerialID.loop(0);
		}
	}

	pinMode(LED_PIN, OUTPUT);

	I2S* i2s = new I2S();
	i2s_driver_uninstall(I2S_NUM_0); //revert wrong i2s config from esp8266audio
	i2s->begin();

	Playback.begin(i2s);
	Recording.begin(i2s);
	IntentStore::fillStorage();

	SerialID.start();
	LoopManager::addListener(&Playback);
	LoopManager::addListener(&LEDmatrix);
	LoopManager::addListener(&TimeService);
	LoopManager::addListener(&UpdateChecker);
	LoopManager::addListener(new InputGPIO());

	Net.set(Settings.get().SSID, Settings.get().pass);
	Net.addStateListener(&TimeService);
	Net.addStateListener(&UpdateChecker);

	State::changeState(new StartupState(!Settings.begin() || Settings.get().SSID[0] == 0));

	LoopManager::setStackSize(10240);
	LoopManager::startTask(2, 1);
}

void loop(){
	vTaskDelete(nullptr);
}