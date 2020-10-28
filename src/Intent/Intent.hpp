#ifndef SPENCER_INTENT_H
#define SPENCER_INTENT_H

#include <Loop/LoopListener.h>
#include "../State/IntentState.h"

class Intent : public LoopListener
{
public:
    virtual ~Intent() = default;

protected:
	static void done(){
		IntentState::intentDone();
	}
};

#endif
