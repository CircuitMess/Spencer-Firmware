#ifndef SPENCER_TEXT2SPEECH_H
#define SPENCER_TEXT2SPEECH_H

#include <HTTPClient.h>
#include <set>
#include "../Util/StreamableHTTPClient.h"
#include "../AsyncProcessor.hpp"

struct TTSJob {
	const char* text;
	const char** resultFilename;
};

class TextToSpeechImpl : public AsyncProcessor<TTSJob> {
public:
	TextToSpeechImpl();

	void releaseRecording(const char* filename);

protected:
	void doJob(const TTSJob& job) override;

private:
	const char* generateSpeech(const char* text, const char* filename = "speech.mp3");
	void processStream(WiFiClient& stream, const char* filename);
	void readUntilQuote(WiFiClient& stream);

	std::set<const char*> fileStash;
	Mutex stashMut;
};

extern TextToSpeechImpl TextToSpeech;
#endif