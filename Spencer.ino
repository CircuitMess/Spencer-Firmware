#include <Arduino.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <CircuitOS.h>
#include <Input/InputGPIO.h>
#include "src/Speech/SpeechToIntent.h"
#include "src/Services/Audio/Audio.h"
#include "Spencer.hpp"
#include "src/LEDmatrix/LEDmatrix.h"
#include <Loop/LoopManager.h>
#include "src/Services/TimeService/TimeService.h"
#include "src/Intent/TimeIntent.h"
#include "src/Util/FlashTools.h"
InputGPIO input;

bool wifiStatus;
void wifiClear()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    wifiStatus = WiFi.status() == WL_CONNECTED;
    delay(100);
}
bool wifiConnect(char *SSID, char *PASS, unsigned short tries)
{
    wifiStatus = WiFi.status() == WL_CONNECTED;
    while ((tries > 0) && (!wifiStatus))
    {
        wifiClear();
        WiFi.begin(SSID, PASS);
        uint32_t startMillis = millis();
        while(millis() - startMillis < 5000 && !wifiStatus)
        {
            wifiStatus = WiFi.status() == WL_CONNECTED;
            delay(100);
        }
        wifiStatus = WiFi.status() == WL_CONNECTED;
        tries--;
        Serial.println(".");
    }
    return wifiStatus;
}


TimeIntent *timeIntent;
void setup(){
	Serial.begin(115200);
	if(!wifiConnect("Grabrik", "Ayy4Imao", 10))
	{
		Serial.println("cant connect");
		while(1);
	}
	else
	{
		Serial.println("connected");
	}

	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	if(!SerialFlash.begin(spi, FLASH_CS_PIN)){
		Serial.println("Flash fail");
		return;
	}

	if(!LEDmatrix.begin())
	{
		Serial.println("couldn't start matrix");
		while(1);
	}
	LEDmatrix.clear();
	LEDmatrix.setBrightness(20);
	LEDmatrix.setRotation(2);
	LoopManager::addListener(&LEDmatrix);

	Audio.begin();
	LoopManager::addListener(&Audio);

	TimeService.fetchTime();
	Serial.print("time: ");
	DateTime now = DateTime(TimeService.getTime());
	Serial.printf("%d:%d:%d\n", now.hour(), now.minute(), now.second());
	Serial.println();
	TimeIntentParam params{TimeIntentType::TIME, TimeService.getTime()};
	timeIntent = new TimeIntent(&params);
}
void loop(){
	LoopManager::loop();
	if(timeIntent != nullptr) timeIntent->loop();
}

