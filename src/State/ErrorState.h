#ifndef SPENCER_ERRORSTATE_H
#define SPENCER_ERRORSTATE_H


#include "State.h"
#include "../Net.h"

enum ErrorType {
	WIFI
};

class ErrorState : public State {
public:
	ErrorState(ErrorType type);

	void enter() override;
	void exit() override;

private:
	ErrorType type;

	void doWifi();

};


#endif //SPENCER_ERRORSTATE_H
