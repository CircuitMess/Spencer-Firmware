#ifndef SPENCER_FLASHTOOLS_H
#define SPENCER_FLASHTOOLS_H

#define MAX_FILENAME 255

#include <FS.h>

class FlashTools {
public:

	/**
	 * Erases all data from the flash chip.
	 */
	static void erase();

	/**
	 * Uploads files from serial to the flash chip. WARNING: this erases all data on the flash.
	 * @see https://github.com/CircuitMess/SerialUploader
	 */
	static void upload();

	/**
	 * Uploads files to the flash chip from SD card. The FS on the SD card will be flattened, replacing
	 * slashes with dashes. Ex. /special/badum.mp3 becomes `special-badum.mp3` on the flash FS.
	 * CS 12 (not used), SCK 13, MISO 14, MOSI 15
	 */
	static void uploadSD();

	static void listFiles();

private:
	static void copyDirSD(File& dir, const char* prefix = "");

};


#endif //SPENCER_FLASHTOOLS_H
