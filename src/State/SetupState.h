#ifndef SETUPSTATE_SPENCER_H
#define SETUPSTATE_SPENCER_H

#include "State.h"
#include <Loop/LoopListener.h>
#include "../SetupServer/SetupServer.h"

class SetupState : public State {
public:
	SetupState();
	virtual ~SetupState();

	void enter() override;
	void exit() override;

private:
	static SetupState* instance;

};


#endif