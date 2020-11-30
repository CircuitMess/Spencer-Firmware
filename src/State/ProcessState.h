#ifndef SPENCER_PROCESSSTATE_H
#define SPENCER_PROCESSSTATE_H


#include <Loop/LoopListener.h>
#include "State.h"
#include <Speech/SpeechToIntent.h>

class ProcessState : public State, public LoopListener {
public:
	ProcessState(const char* recordingFilename);

	void enter() override;
	void exit() override;
	void loop(uint micros) override;

private:
	const char* recordingFilename;

	IntentResult* intentResult = nullptr;
	bool retried = false;

	void processIntent();

	void bleep();

};


#endif //SPENCER_PROCESSSTATE_H
