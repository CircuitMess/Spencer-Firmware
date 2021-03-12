#include <Arduino.h>
#include <Spencer.h>
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

	if(checkJig()){
		disableCore0WDT();
		disableCore1WDT();

		HardwareTest test;
		test.start();
		for(;;);
	}
	Spencer.begin();

	IntentStore::fillStorage();

	SerialID.start();
	LoopManager::addListener(&TimeService);
	LoopManager::addListener(&UpdateChecker);

	Net.addStateListener(&TimeService);
	Net.addStateListener(&UpdateChecker);

	bool firstTime = Spencer.loadSettings();
	State::changeState(new StartupState(firstTime));

	LoopManager::startTask(2, 1);
}

void loop(){
	vTaskDelete(nullptr);
}