#ifndef SPENCER_LISTENSTATE_H
#define SPENCER_LISTENSTATE_H

#include "State.h"

class ListenState : public State {
public:
	ListenState();
	~ListenState() override;

	void enter() override;
	void exit() override;

private:

};


#endif //SPENCER_LISTENSTATE_H
