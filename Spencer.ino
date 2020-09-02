#include <Arduino.h>
#include <SPI.h>
#include "src/Services/Audio/Audio.h"
#include <AudioOutputI2S.h>
#include <AudioGeneratorWAV.h>
#include <AudioGeneratorMP3.h>
#include "Spencer.hpp"

AudioGeneratorWAV *wav;
AudioGeneratorMP3 *mp3;
AudioOutputI2S *out;
AudioFileSourceSerialFlash *file;
Audio audio;

void spaces(int num) {
  for (int i=0; i < num; i++) {
    Serial.print(" ");
  }
}

void setup(){
	Serial.begin(115200);
	SPIClass spi(3);
	spi.begin(18, 19, 23, 26);
	if(!SerialFlash.begin(spi, 26))
	{
		Serial.println("flash error");
	}
	// audio.begin();
	// audio.record([](byte* data, size_t size){

	// });
	// i2s_stop(I2S_NUM_0);

	// create the file on the Flash chip and copy data
	// SerialFlash.opendir();
	// char* filename = "test.txt";
	// uint length = 255;
    if (SerialFlash.exists("1.mp3")) {
		Serial.println("exists");
    }
	else
	{
		Serial.println("doesnt exist");
	}
	
	

	// SerialFlash.opendir();
	// SerialFlash.readdir(buffer, buflen, filelen);
	file = new AudioFileSourceSerialFlash();
	if(!file->open("1.mp3"))
	{
		Serial.println("error opening file");
		delay(10000);
	}
	// wav = new AudioGeneratorWAV();
	mp3 = new AudioGeneratorMP3();
	out = new AudioOutputI2S(0,0,16,-1);
	out->SetRate(16000);
	out->SetPinout(16, 21, 4);
	out->SetBitsPerSample(32);
	out->SetChannels(1);
	out->SetOutputModeMono(1);
	out->SetGain(1);
	
	mp3->begin(file, out);
}

void loop(){
	if (mp3->isRunning()) {
		if (!mp3->loop()){
			mp3->stop();
		}
	}
	else {
		Serial.printf("WAV done\n");
		delay(1000);
	}
}
