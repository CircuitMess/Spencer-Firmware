#ifndef SPENCER_INTENTSTATE_H
#define SPENCER_INTENTSTATE_H

#include <Loop/LoopListener.h>
#include "State.h"
#include "../Intent/IntentInfo.hpp"

class Intent;

class IntentState : public State, public LoopListener {
public:
	IntentState(Intent* intent, IntentInfo::Upsell* upsell);
	virtual ~IntentState();

	void enter() override;
	void exit() override;

	void loop(uint micros) override;

	static void intentDone();

private:
	static IntentState* instance;

	Intent* intent;
	IntentInfo::Upsell* upsell;

};


#endif //SPENCER_INTENTSTATE_H
