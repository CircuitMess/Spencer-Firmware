#ifndef SPENCER_STATE_H
#define SPENCER_STATE_H

class State {
public:
	virtual ~State() = default;
	virtual void enter() = 0;
	virtual void exit() = 0;

	static void changeState(State* state);

protected:
	static State* currentState;

};

#endif //SPENCER_STATE_H
