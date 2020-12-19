#ifndef SPENCER_UPDATECHECKER_H
#define SPENCER_UPDATECHECKER_H


#include <Loop/LoopListener.h>
#include <Util/Task.h>
#include <Net/Net.h>

class UpdateCheckerImpl : public LoopListener, public NetStateListener {
public:
	UpdateCheckerImpl();
	void loop(uint micros) override;

	bool updateAvailable();

	bool hasNotified();
	void notify();

private:
	Task checkTask;
	bool checking = false;
	uint checkTime = 0;

	bool running = false;

	uint version = 0;
	uint notifiedVersion;

	void checkVersion();

	void state(wl_status_t status) override;

};

extern UpdateCheckerImpl UpdateChecker;

#endif //SPENCER_UPDATECHECKER_H
