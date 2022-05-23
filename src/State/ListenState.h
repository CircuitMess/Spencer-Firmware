#ifndef SPENCER_LISTENSTATE_H
#define SPENCER_LISTENSTATE_H

#include <Loop/LoopListener.h>
#include "State.h"

class MatrixAnimGIF;
struct IntentResult;

class ListenState : public State, public LoopListener {
public:
	ListenState();
	~ListenState() override;

	void enter() override;
	void exit() override;

	void loop(uint micros) override;

private:
	const char* recordResult = nullptr;
	MatrixAnimGIF* anim = nullptr;

};


#endif //SPENCER_LISTENSTATE_H
