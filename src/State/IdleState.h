#ifndef SPENCER_IDLESTATE_H
#define SPENCER_IDLESTATE_H

#include "State.h"

class IdleState : public State {
public:
	IdleState();
	virtual ~IdleState();

	void enter() override;
	void exit() override;

private:
	static IdleState* instance;

};


#endif //SPENCER_IDLESTATE_H
