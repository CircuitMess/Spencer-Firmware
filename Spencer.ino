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
LEDmatrix ledmatrix;

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


// TimeIntent *timeIntent;
void setup(){
	// Serial.begin(115200);
	// if(!wifiConnect("Grabrik", "Ayy4Imao", 10))
	// {
	// 	Serial.println("cant connect");
	// 	while(1);
	// }
	// else
	// {
	// 	Serial.println("connected");
	// }
	// SPIClass spi(3);
	// spi.begin(18, 19, 23, FLASH_CS_PIN);
	// if(!SerialFlash.begin(spi, FLASH_CS_PIN)){
	// 	Serial.println("Flash fail");
	// 	return;
	// }
	// if(!ledmatrix.begin())
	// {
	// 	Serial.println("couldn't start matrix");
	// 	while(1);
	// }
	// ledmatrix.clear();
	// ledmatrix.setBrightness(20);
	// ledmatrix.setRotation(2);


	// TimeService.fetchTime();
	// Serial.print("unixtime: ");
	// Serial.println(TimeService.getTime());
	// TimeIntent timeintent = TimeIntent((void*)(TimeService.getTime()));

	
	AudioFileSource* source = SampleStore::load(Generic, "HELLO");
	if(!source->isOpen()){
		Serial.println("Failed opening sample");
		for(;;);
	}
	source->seek(16000, SEEK_SET);
	Audio.begin();
	Audio.playMP3(source);
}
void loop(){
	// Audio.loop();
}

