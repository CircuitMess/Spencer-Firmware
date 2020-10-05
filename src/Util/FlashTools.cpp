#include <SerialFlash.h>
#include "FlashTools.h"

void FlashTools::erase(){
	SerialFlash.eraseAll();
	while(!SerialFlash.ready());
}

void FlashTools::upload(){
	Serial.setTimeout(30000);
	Serial.println("Waiting for serial upload");

	while(!Serial.available());
	char upload[6];
	Serial.readBytes(upload, 6);
	if(strncmp(upload, "upload", 6)){
		Serial.printf("Expected 'upload', gotten '%.6s'\n", upload);
		return;
	}

	Serial.print("erase");
	erase();
	Serial.print("ready");

	while(!Serial.available());

	char filename[MAX_FILENAME + 1];
	uint32_t filesize;
	while(true){
		Serial.readBytes(filename, MAX_FILENAME + 1);
		if(strncmp(filename, "end", 3) == 0) break;

		Serial.readBytes(reinterpret_cast<char*>(&filesize), sizeof(uint32_t));

		if(SerialFlash.exists(filename)){
			SerialFlash.remove(filename);
		}

		SerialFlash.create(filename, filesize);
		SerialFlashFile file = SerialFlash.open(filename);

		size_t fileWritten = 0;
		uint32_t sum = 0;
		while(fileWritten < filesize){
			byte data[256];
			size_t bytes = Serial.readBytes(data, min((size_t) 256, filesize - fileWritten));

			file.write(data, bytes);
			fileWritten += bytes;

			for(int i = 0; i < bytes; i += sizeof(uint32_t)){
				sum += *reinterpret_cast<uint32_t*>(&data);
			}
		}
		file.close();

		Serial.write(reinterpret_cast<uint8_t*>(&sum), sizeof(uint32_t));
	}

	Serial.setTimeout(1000);
}

void FlashTools::listFiles(){
	SerialFlash.opendir();
	while(1){
		char filename[64];
		uint32_t filesize;

		if(SerialFlash.readdir(filename, sizeof(filename), filesize)){
			Serial.print("  ");
			Serial.print(filename);
			for(int i = 0; i < 40 - (int) strlen(filename); i++) Serial.print(" ");
			Serial.print("  ");
			Serial.print(filesize);
			Serial.print(" bytes");
			Serial.println();
		}else{
			break; // no more files
		}
	}
}
