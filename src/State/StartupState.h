#ifndef SPENCER_STARTUPSTATE_H
#define SPENCER_STARTUPSTATE_H

#include <Arduino.h>
#include <Loop/LoopListener.h>
#include "State.h"
#include <Network/Net.h>

class StartupState : public State, public LoopListener {
public:
	explicit StartupState(bool firstTime);

	void enter() override;
	void exit() override;
	void loop(uint micros) override;

private:
	uint32_t startupEnd;
	bool firstTime;
};


#endif //SPENCER_STARTUPSTATE_H
