#include <SerialFlash.h>
#include "FlashTools.h"

void FlashTools::erase(){
	SerialFlash.eraseAll();
	while(!SerialFlash.ready());
}

void FlashTools::upload(){
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
		while(fileWritten < filesize){
			byte data[256];
			size_t bytes = Serial.readBytes(data, min((size_t) 256, filesize - fileWritten));

			file.write(data, bytes);
			fileWritten += bytes;
		}

		file.close();
	}
}

void FlashTools::listFiles(){
	SerialFlash.opendir();
	while(1){
		char filename[64];
		uint32_t filesize;

		if(SerialFlash.readdir(filename, sizeof(filename), filesize)){
			Serial.print("  ");
			Serial.print(filename);
			for(int i = 0; i < 20 - strlen(filename); i++) Serial.print(" ");
			Serial.print("  ");
			Serial.print(filesize);
			Serial.print(" bytes");
			Serial.println();
		}else{
			break; // no more files
		}
	}
}
