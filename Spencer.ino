#include <Arduino.h>
#include <SPI.h>
#include "src/Services/Audio/Audio.h"

#include "Spencer.hpp"
#include <CircuitOS.h>
#include <Input/InputGPIO.h>
#include <AudioLogger.h>

InputGPIO input;

Audio audio;
CompositeAudioFileSource sentence;
AudioFileSourceSerialFlash first;
AudioFileSourceSerialFlash second;
void spaces(int num) {
  for (int i=0; i < num; i++) {
    Serial.print(" ");
  }
}

void setup(){
	Serial.begin(115200);

	audioLogger = &Serial; 
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

	first = AudioFileSourceSerialFlash("1-j.mp3");
	second = AudioFileSourceSerialFlash("2.mp3");
	sentence.add(&first);
	sentence.add(&second);
	sentence.add(&first);
	audio.begin();

	input.setBtnPressCallback(17, [](){
		audio.play(&sentence, 1);
		// Serial.println("start recording!");
		// audio.record([](){
		// 	Serial.println("record done");
		// 	audio.play("recording.wav");
		// });
	});
}

void loop(){
	input.loop(0);
	audio.loop();
}