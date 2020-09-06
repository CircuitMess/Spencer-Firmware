#include <Arduino.h>
#include <SPI.h>
#include "src/Services/Audio/Audio.h"
#include <AudioOutputI2S.h>
#include <AudioGeneratorWAV.h>
#include <AudioGeneratorMP3.h>
#include "Spencer.hpp"
#include <CircuitOS.h>
#include <Input/InputGPIO.h>

InputGPIO input;
AudioGeneratorWAV *wav = nullptr;
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
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	if(!SerialFlash.begin(spi, FLASH_CS_PIN))
	{
		Serial.println("flash error");
	}
	// Serial.println("erasing");
	// SerialFlash.eraseAll();
	while (!SerialFlash.ready());
	Serial.println("ready");

	
	// if(!SerialFlash.create("test.txt", 20))
	// {
	// 	Serial.println("can't create file");
	// }
	// SerialFlashFile writeFile = SerialFlash.open("test.txt");
	// writeFile.write("This is a test.", 15);
	// writeFile.close();
	// if(!SerialFlash.exists("test.txt"))
	// {
	// 	Serial.println("doesnt exist");
	// }
	// SerialFlashFile readFile = SerialFlash.open("test.txt");
	// char buffer[10] = {0};
	// readFile.read(buffer, sizeof(buffer));
	// for(uint8_t i = 0; i < 10; i++)
	// {
	// 	Serial.print(buffer[i]);
	// }
	// Serial.println();

	input.setBtnPressCallback(17, [](){
		audio.begin();
		Serial.println("start recording!");
		audio.record([](byte* data, size_t size){

		});
		Serial.println("record done");

		if(SerialFlash.exists("recording.wav"))
		{
			Serial.println("exists");
		}
		else
		{
			Serial.println("doesnt exist");
		}
		// SerialFlashFile readfile = SerialFlash.open("recording.wav");
		// Serial.println(readfile.getFlashAddress());		
		// char buffer[10] = {0};
		// uint32_t readBytes = sizeof(buffer);
		// for(uint8_t i = 0; i < 5; i++)
		// {
		// 	readBytes = readfile.read(buffer, 10);
		// 	for(uint8_t i = 0; i < readBytes; i++)
		// 	{
		// 		Serial.print(buffer[i]);
		// 	}
		// }
		// Serial.println();
		// readfile.close();


		// int sample = 0;
		// readfile = SerialFlash.open("recording.wav");
		// readBytes = sizeof(sample);
		// while(readBytes >= sizeof(sample))
		// {
		// 	readBytes = readfile.read(&sample, sizeof(sample));
		// 	Serial.print(sample);
		// 	Serial.printf(", %d, %d\n", -(std::numeric_limits<int32_t>::max()), std::numeric_limits<int32_t>::max());
		// }

		
	});

	if(SerialFlash.exists("recording.wav"))
	{
		Serial.println("exists");
	}
	else
	{
		Serial.println("doesnt exist");
	}
	SerialFlashFile readfile = SerialFlash.open("recording.wav");
	Serial.println(readfile.getFlashAddress());		
	char buffer[10] = {0};
	uint32_t readBytes = sizeof(buffer);
	for(uint8_t i = 0; i < 5; i++)
	{
		readBytes = readfile.read(buffer, 10);
		for(uint8_t i = 0; i < readBytes; i++)
		{
			Serial.print(buffer[i]);
		}
	}
	Serial.println();
	readfile.close();

	file = new AudioFileSourceSerialFlash();
	if(!file->open("recording.wav"))
	{
		Serial.println("error opening file");
		// delay(10000);
	}

	audio.begin();
	// i2s_stop(I2S_NUM_0);
	wav = new AudioGeneratorWAV();
	// mp3 = new AudioGeneratorMP3();
	out = new AudioOutputI2S(0,0,16,-1);
	
	out->SetRate(16000);
	out->SetPinout(16, 21, 4);
	out->SetBitsPerSample(16);
	out->SetChannels(1);
	out->SetOutputModeMono(1);
	out->SetGain(0.5);
	// mp3->begin(file, out);
	wav->begin(file, out);
}

void loop(){
	input.loop(micros());
	if(wav != nullptr)
	{
		if (wav->isRunning()) {
			if (!wav->loop()){
				wav->stop();
			}
		}
		else {
			Serial.printf("WAV done\n");
			delay(1000);
		}
	}
}