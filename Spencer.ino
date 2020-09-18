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
curl -H ""Content-Type": "application/json"; charset=utf-8" --data "{
  "input":{
    "text":"One."
  },
  "voice":{
    "languageCode":"en-US",
    "name":"en-US-Standard-D",
    "ssmlGender":"NEUTRAL"
  },
  "audioConfig":{
    "audioEncoding":"MP3",
	"speakingRate":"0.96",
	"pitch":"7.2"
  }
}" "https://texttospeech.googleapis.com/v1/text:synthesize?key=secret"
