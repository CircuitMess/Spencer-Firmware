#include <Util/Task.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <SerialFlash.h>
#include "HardwareTest.h"
#include <Settings.h>
#include <Audio/I2S.h>
#include <Spencer.h>
#include "Util/FlashTools.h"

HardwareTest* HardwareTest::test = nullptr;

HardwareTest::HardwareTest(){
	test = this;

	tests.push_back({ HardwareTest::audio, "Audio" });
	tests.push_back({ HardwareTest::wifi, "WiFi" });
	tests.push_back({ HardwareTest::flashInit, "Flash init" });
	tests.push_back({ HardwareTest::flashErase, "Flash erase" });
	tests.push_back({ HardwareTest::F2FdataUpload, "Data upload" });
	tests.push_back({ HardwareTest::dataVerify, "Data verify" });
}

void HardwareTest::waitID(){
	int cursor;
	char sig[2];

	for(;;){
		while(!Serial.available());

		cursor = (cursor + 1) % 2;
		sig[cursor] = Serial.read();

		int matches = 0;
		for(int i = 0; i < 2; i++){
			int c = (i + cursor + 1) % 2;
			matches += sig[c] == "ID"[i];
		}

		if(matches == 2) break;
	}

	Serial.printf("Spencer:%d\n", Settings.get().calibrated);
}

void HardwareTest::waitStart(){
	int cursor;
	char sig[10];

	for(;;){
		while(!Serial.available());

		cursor = (cursor + 1) % 10;
		sig[cursor] = Serial.read();

		int matches = 0;
		for(int i = 0; i < 10; i++){
			int c = (i + cursor + 1) % 10;
			matches += sig[c] == "TEST:START"[i];
		}

		if(matches == 10) break;
	}
}

void HardwareTest::start(){
	waitStart();

	Serial.println();
	uint64_t mac = ESP.getEfuseMac();
	uint32_t upper = mac >> 32;
	uint32_t lower = mac & 0xffffffff;
	Serial.printf("TEST:begin:%x%x\n", upper, lower);

	bool pass = true;
	for(const Test& test : tests){
		currentTest = test.name;

		Serial.printf("TEST:startTest:%s\n", currentTest);
		bool result = test.test();
		Serial.printf("TEST:endTest:%s\n", result ? "pass" : "fail");

		if(!(pass &= result)) break;
	}

	if(pass){
		Serial.println("TEST:passall");
	}else{
		Serial.printf("TEST:fail:%s\n", currentTest);
	}

	Settings.begin();
	Settings.get().calibrated = pass;
	Settings.store();
}

bool HardwareTest::audio(){
	I2S* i2s = new I2S();
	i2s_driver_uninstall(I2S_NUM_0); //revert wrong i2s config from esp8266audio
	i2s->begin();

	Task waveTask("Wave", [](Task* task){
		size_t bufferSize;
		int16_t* buffer = nullptr;
		float currentFreq;

		auto generate = [&bufferSize, &buffer](float freq){
			int numSamples = ceil(16000.0f / freq);
			float omega = 2.0f * M_PI * freq;
			float timeDelta = (1.0f / freq) / (float) numSamples;
			float amp = 2000; // amplitude (max is 2^15 - 1)

			bufferSize = numSamples * 2 * sizeof(int16_t);
			buffer = static_cast<int16_t*>(realloc(buffer, bufferSize));
			for(int i = 0; i < numSamples; i++){
				buffer[i * 2 + 1] = sin(omega * timeDelta * (float) i) * amp;
			}
		};

		size_t bytesWritten;

		while(task->running){
			float freq = *static_cast<float*>(task->arg);
			if(freq == 0) continue;
			if(freq != currentFreq){
				generate(freq);
				currentFreq = freq;
			}

			i2s_write(I2S_NUM_0, buffer, bufferSize, &bytesWritten, portMAX_DELAY);
		}

		free(buffer);
	});

	float currentFreq = 0;
	waveTask.arg = &currentFreq;

	int numSamples = 128;
	size_t i2sBufferSize = numSamples * 2 * sizeof(int16_t);
	char* i2sBuffer = static_cast<char*>(malloc(i2sBufferSize));
	int16_t* buffer = static_cast<int16_t*>(malloc(i2sBufferSize / 2));
	memset(buffer, 0, i2sBufferSize / 2);

	struct cmplx {
		float re;
		float im;
	};
	float W = 2.0f * M_PI / (float) numSamples;
	cmplx* X = static_cast<cmplx*>(malloc(numSamples * sizeof(cmplx)));

	auto recordFreq = [&currentFreq, &i2s, buffer, i2sBuffer, i2sBufferSize](float freq){
		currentFreq = freq;

		// Pre-record
		for(int i = 0; i < 100; i++){
			i2s->Read(i2sBuffer, i2sBufferSize);
		}

		// Record
		for(int j = 0; j < i2sBufferSize; j += 4){
			int16_t sample = *(int16_t*) (&i2sBuffer[j + 2]) + 3705;
			buffer[j / 4] = sample;
		}
	};

	auto testFreq = [recordFreq, buffer, numSamples, W, X](float freq) -> bool{
		recordFreq(freq);

		// DFT
		for(int i = 0; i < numSamples; i++){
			X[i].re = X[i].im = 0;

			for(int j = 0; j < numSamples; j++){
				X[i].re += (float) buffer[j] * cos(W * (float) i * (float) j);
				X[i].im -= (float) buffer[j] * sin(W * (float) i * (float) j);
			}
		}

		auto f = [X](size_t i) -> float{
			return sqrt(pow(X[i].re, 2) + pow(X[i].im, 2));
		};

		int target = round((float) numSamples * freq / 16000.0f);

		float targetFreq = f(target);

		test->log("amp", targetFreq);

		return targetFreq > 50000
			   && targetFreq > 3.0f * f(target - 3)
			   && targetFreq > 3.0f * f(target - 2)
			   && targetFreq > 3.0f * f(target + 2)
			   && targetFreq > 3.0f * f(target + 3);
	};

	waveTask.start(2, 0);
	delay(500);

	bool pass = testFreq(500)
				&& testFreq(750)
				&& testFreq(1250);


	i2s->stop();
	waveTask.stop();
	delay(500);

	return pass;
}

bool HardwareTest::wifi(){
	wl_status_t status;

	for(int i = 0; i < 3; i++){
		WiFi.disconnect(true);
		WiFi.persistent(false);
		WiFi.begin("CircuitMess", "MAKERphone!");
		WiFi.setSleep(false);
		delay(100);

		uint32_t startTime = millis();
		status = WiFi.status();

		while(!status || status >= WL_DISCONNECTED){
			delay(500);
			status = WiFi.status();
			if(millis() - startTime > 10000) break;
		}

		if(status == WL_CONNECTED) break;
	}

	if(status != WL_CONNECTED){
		test->log("reason", "WiFi connection");
		return false;
	}

	HTTPClient client;
	client.setConnectTimeout(2000);
	client.useHTTP10(true);
	client.setReuse(false);

	if(!client.begin("http://spencer.circuitmess.com:7979/index")){
		client.end();
		client.getStream().flush();
		test->log("reason", "Client begin");
		return false;
	}

	client.setUserAgent("Spencer");

	int code = client.GET();
	if(code != 200){
		client.end();
		client.getStream().flush();
		char data[64];
		sprintf(data, "HTTP code %d", code);
		test->log("reason", data);
		return false;
	}

	String data = client.getString();
	client.end();
	client.getStream().flush();

	bool pass = data.substring(0, 2) == "OK";

	if(!pass){
		test->log("reason", "Wrong response");
	}

	return pass;
}

bool HardwareTest::flashInit(){
	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	return SerialFlash.begin(spi, FLASH_CS_PIN);
}

bool HardwareTest::flashErase(){
	SerialFlash.eraseAll();
	while(!SerialFlash.ready()){
		delay(100);
	}
	SerialFlash.setSettings(SPISettings(30000000, MSBFIRST, SPI_MODE0));
	return true;
}

bool HardwareTest::dataUpload(){
	uint32_t time = FlashTools::uploadSDSilent();
	if(time < 1000) return false;
	test->log("time", time);
	return true;
}

bool HardwareTest::F2FdataUpload(){
	bool inited = false;
	int tries = 0;

	SPIClass spi2(2);
	spi2.begin(13, 14, 15, 12);
	SerialFlashChip flash2(spi2);
	flash2.setSettings(SPISettings(20000000, MSBFIRST, SPI_MODE0));

	while(!inited && tries++ < 10){
		inited = flash2.begin(12);

		if(!inited){
			delay(100);
		}
	}

	if(!inited){
		test->log("FLASH", "fatal");
		return false;
	}

	char filename[128];
	uint32_t filesize;
	unsigned char buffer[256];

	uint32_t startTime = millis();

	currentFlash = &flash2;
	flash2.opendir();
	while(flash2.readdir(filename, 128, filesize)){
		currentFlash = &SerialFlash;
		if(!SerialFlash.create(filename, filesize)){
			char message[128];
			sprintf(message, "failed creating %s", filename);
			test->log("reason", message);
			return false;
		}

		currentFlash = &flash2;
		SerialFlashFile source = flash2.open(filename);

		currentFlash = &SerialFlash;
		SerialFlashFile destination = SerialFlash.open(filename);

		if(!source){
			char message[128];
			sprintf(message, "failed opening source %s", filename);
			test->log("reason", message);
			return false;
		}

		if(!destination){
			char message[128];
			sprintf(message, "failed opening destination %s", filename);
			test->log("reason", message);
			return false;
		}

		uint32_t bytesRead;
		currentFlash = &flash2;
		while((bytesRead = source.read(buffer, 256))){
			currentFlash = &SerialFlash;
			destination.write(buffer, bytesRead);
			currentFlash = &flash2;
		}

		source.close();
		destination.close();

		currentFlash = &flash2;
	}

	currentFlash = &SerialFlash;

	test->log("time", (uint) (millis() - startTime));
	return true;
}

bool HardwareTest::dataVerify(){
	uint32_t primes[] = { 3, 7, 13, 17, 19, 23, 27, 29, 31 };
	int noPrimes = sizeof(primes) / sizeof(primes[0]);

	char filename[128];
	uint32_t filesize;
	unsigned char buffer[256];

	uint32_t startTime = millis();
	uint32_t noFiles = 0;

	SerialFlash.opendir();
	while(SerialFlash.readdir(filename, 128, filesize)){
		noFiles++;
		SerialFlashFile file = SerialFlash.open(filename);
		uint32_t hash = 0;
		int primePtr = 0;

		uint32_t bytesRead;
		while((bytesRead = file.read(buffer, 256))){
			for(int i = 0; i < bytesRead; i++){
				hash += buffer[i] * primes[primePtr++];

				if(primePtr >= noPrimes){
					primePtr = 0;
				}
			}
		}

		Serial.printf("DATA:%s:%u\n", filename, hash);

		while(!Serial.available());
		char status[2];
		Serial.readBytes(status, 2);
		if(status[0] != 'O' || status[1] != 'K'){
			char data[128];
			sprintf(data, "%s %u", filename, hash);
			test->log("checksum missmatch", data);
			return false;
		}
	}

	Serial.println("DATA:DONE");

	while(!Serial.available());
	char status[2];
	Serial.readBytes(status, 2);
	if(status[0] != 'O' || status[1] != 'K'){
		test->log("file number", noFiles);
		return false;
	}

	test->log("time", (uint32_t) (millis() - startTime));

	return true;
}

void HardwareTest::log(const char* property, char* value){
	Serial.printf("%s:%s:%s\n", currentTest, property, value);
}

void HardwareTest::log(const char* property, float value){
	Serial.printf("%s:%s:%f\n", currentTest, property, value);
}

void HardwareTest::log(const char* property, double value){
	Serial.printf("%s:%s:%lf\n", currentTest, property, value);
}

void HardwareTest::log(const char* property, bool value){
	Serial.printf("%s:%s:%d\n", currentTest, property, value ? 1 : 0);
}

void HardwareTest::log(const char* property, uint32_t value){
	Serial.printf("%s:%s:%u\n", currentTest, property, value);
}
