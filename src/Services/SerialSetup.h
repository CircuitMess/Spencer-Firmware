#ifndef SPENCER_SERIALSETUP_H
#define SPENCER_SERIALSETUP_H


#include <Loop/LoopListener.h>

class SerialSetup : public LoopListener {
public:
	void loop(uint micros) override;

	void setSettingsSetCallback(void (* connectCallback)());

private:
	char sig[3];
	uint8_t cursor = 0;

	void readSettings();

	void readIntoBuffer(char* buffer, int limit);
	void clearNL();

	void (*settingsSetCallback)() = nullptr;
};


#endif //SPENCER_SERIALSETUP_H
