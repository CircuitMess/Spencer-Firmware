#ifndef SPENCER_INTENTSTATE_H
#define SPENCER_INTENTSTATE_H

#include <Loop/LoopListener.h>
#include "State.h"
#include "../Intent/Intent.hpp"

class IntentState : public State, public LoopListener {
public:
	IntentState(Intent* intent);

	void enter() override;
	void exit() override;

	void loop(uint micros) override;

private:
	Intent* intent;

};


#endif //SPENCER_INTENTSTATE_H
