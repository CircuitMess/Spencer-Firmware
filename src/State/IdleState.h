#ifndef SPENCER_IDLESTATE_H
#define SPENCER_IDLESTATE_H

#include "State.h"
#include <Loop/LoopListener.h>

class MatrixAnimGIF;

class IdleState : public State, public LoopListener{
public:
	IdleState();
	virtual ~IdleState();

	void enter() override;
	void exit() override;
	void loop(uint _micros) override;

private:
	static IdleState* instance;
	static const uint totalAnimations = 12;
	std::vector<uint> usedIdleAnimations;
	std::vector<uint> unusedIdleAnimations;
	void startRandomAnimation();
	uint8_t animationLoopCounter = 0;
	bool animationLoopDone = 0;
	int8_t requiredAnimationLoops = 0;
	bool notifyingUpdate = false;

	MatrixAnimGIF* anim = nullptr;
};


#endif //SPENCER_IDLESTATE_H
