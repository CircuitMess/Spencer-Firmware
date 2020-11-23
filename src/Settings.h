#ifndef SPENCER_SETTINGS_H
#define SPENCER_SETTINGS_H

#include <Arduino.h>

struct SettingsData {
	char SSID[64] = {0};
	char pass[64] = {0};
	char google_key[40] = {0};
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
