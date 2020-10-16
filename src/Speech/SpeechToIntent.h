#ifndef SPENCER_SPEECH2INTENT_H
#define SPENCER_SPEECH2INTENT_H

#include <HTTPClient.h>
#include "../Util/StreamableHTTPClient.h"

struct IntentResult {
	const char* transcript;
	const char* intent;
	float confidence;
};

class SpeechToIntentImpl {
public:
	SpeechToIntentImpl();
	void identifyVoice(void (* callback)(IntentResult*), const char* fileName = "recording.wav");

};

extern SpeechToIntentImpl SpeechToIntent;
#endif