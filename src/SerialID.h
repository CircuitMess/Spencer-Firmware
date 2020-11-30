#ifndef SPENCER_SERIALID_H
#define SPENCER_SERIALID_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Loop/LoopListener.h>

class SerialIDImpl : public LoopListener {
public:
	void loop(uint micros) override;

	void start();
	void stop();

private:
	char last = 0;
	
};

extern SerialIDImpl SerialID;

#endif //SPENCER_SERIALID_H
