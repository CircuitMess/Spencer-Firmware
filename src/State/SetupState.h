#ifndef SETUPSTATE_SPENCER_H
#define SETUPSTATE_SPENCER_H

#include "State.h"
#include <Loop/LoopListener.h>
#include "../SetupServer/SetupServer.h"
#include "../Services/SerialSetup.h"

class MatrixAnimGIF;

class SetupState : public State {
public:
	SetupState();
	virtual ~SetupState();

	void enter() override;
	void exit() override;

private:
	SerialSetup setup;
	static MatrixAnimGIF* anim;

};


#endif