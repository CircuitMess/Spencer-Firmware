#ifndef SPENCER_SERIALSETUP_H
#define SPENCER_SERIALSETUP_H


#include <Loop/LoopListener.h>
#include <Util/Task.h>

class SerialSetup : public LoopListener {
public:
	SerialSetup();

	void loop(uint micros) override;

	void setSettingsSetCallback(void (* connectCallback)());

	void start();
	void stop();

private:
	char sig[3];
	uint8_t cursor = 0;

	Task scanTask;
	bool scanning = false;

	void readSettings();
	void printSettings();
	void printScan();

	void readIntoBuffer(char* buffer, int limit);
	void clearNL();

	void (*settingsSetCallback)() = nullptr;

	enum Option { NONE, SET, GET, SCN };

	Option getOption();
	bool checkOption(const char* option);
};


#endif //SPENCER_SERIALSETUP_H
