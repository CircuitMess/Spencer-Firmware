#ifndef NIBBLE_HWTEST_H
#define NIBBLE_HWTEST_H

#include <Util/Vector.h>

struct Test {
	bool (* test)();
	const char* name;
};

class HardwareTest {
public:
	HardwareTest();
	void start();

private:
	static HardwareTest* test;

	Vector<Test> tests;
	const char* currentTest;

	void waitID();
	void waitStart();

	static bool audio();
	static bool wifi();
	static bool flashInit();
	static bool flashErase();
	static bool dataUpload();
	static bool F2FdataUpload();
	static bool dataVerify();

	void log(const char* property, char* value);
	void log(const char* property, float value);
	void log(const char* property, double value);
	void log(const char* property, bool value);
	void log(const char* property, uint32_t value);
};


#endif