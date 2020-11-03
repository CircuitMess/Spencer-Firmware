#ifndef SPENCER_SETTINGS_H
#define SPENCER_SETTINGS_H

#include <Arduino.h>

struct SettingsData {

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
