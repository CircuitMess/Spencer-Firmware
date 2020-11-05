#ifndef SETUPSTATE_SPENCER_H
#define SETUPSTATE_SPENCER_H

#include "State.h"
#include <Loop/LoopListener.h>
#include "../HTTPserver/HTTPserver.h"
class SetupState : public State, public LoopListener {
public:
	SetupState();
	virtual ~SetupState();

	void enter() override;
	void exit() override;
	void loop(uint _time) override;

private:
	static SetupState* instance;
	HTTPserver server;

};


#endif