#ifndef SPENCER_SPEECH2INTENT_H
#define SPENCER_SPEECH2INTENT_H

#include <queue>
#include <Sync/BinarySemaphore.h>
#include <Sync/Mutex.h>
#include <Util/Task.h>

struct IntentResult {
	const char* transcript;
	const char* intent;
	float confidence;
};

struct STIJob {
	const char* recordingFilename;
	IntentResult** result;
};

class SpeechToIntentImpl {
public:
	SpeechToIntentImpl();

	/**
	 * Add a job to the STI queue. When completed, *job.result will point to an instance of IntentResult.
	 * Ownership of the object is transferred to the caller, and should be deallocated after use.
	 * * @param job
	 */
	void addJob(const STIJob& job);
	void loop();

	[[noreturn]] static void taskFunc(Task* task);

private:
	Task task;
	BinarySemaphore semaphore;
	std::queue<STIJob> jobs;
	Mutex jobsMutex;


	IntentResult* identifyVoice(const char* filename);

};

extern SpeechToIntentImpl SpeechToIntent;
#endif