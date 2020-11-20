#ifndef SPENCER_SPEECH2INTENT_H
#define SPENCER_SPEECH2INTENT_H

#include <queue>
#include <Sync/BinarySemaphore.h>
#include <Sync/Mutex.h>
#include <Util/Task.h>
#include "../AsyncProcessor.hpp"

struct IntentResult {
	enum { OK = 0, OFFLINE, NETWORK, FILE, JSON, INTENT } error;
	const char* transcript;
	const char* intent;
	float confidence;
};

struct STIJob {
	const char* recordingFilename;
	IntentResult** result;
};

class SpeechToIntentImpl : public AsyncProcessor<STIJob> {
public:
	SpeechToIntentImpl();

protected:
	void doJob(const STIJob& job) override;

private:
	IntentResult* identifyVoice(const char* filename);

};

extern SpeechToIntentImpl SpeechToIntent;
#endif