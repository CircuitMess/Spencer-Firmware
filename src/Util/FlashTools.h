#ifndef SPENCER_FLASHTOOLS_H
#define SPENCER_FLASHTOOLS_H

#define MAX_FILENAME 255

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

	static void listFiles();

private:

};


#endif //SPENCER_FLASHTOOLS_H
