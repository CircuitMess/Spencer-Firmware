#ifndef SPENCER_SETTINGS_H
#define SPENCER_SETTINGS_H

#include <Arduino.h>

struct SettingsData {
	char SSID[64];
	char pass[64];
	char TTS_key[40];
	char STT_key[40];
};

class SettingsImpl {
public:
	bool begin();

	void store();

	SettingsData& get();

	/**
	 * Resets the data (to zeroes). Doesn't store.
	 */
	void reset();

private:
	SettingsData data;

};

extern SettingsImpl Settings;

#endif //SPENCER_SETTINGS_H
