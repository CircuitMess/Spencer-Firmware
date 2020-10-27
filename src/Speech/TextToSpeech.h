#ifndef SPENCER_TEXT2SPEECH_H
#define SPENCER_TEXT2SPEECH_H

#include <HTTPClient.h>
#include "../Util/StreamableHTTPClient.h"

class TextToSpeechImpl {
public:
	TextToSpeechImpl();
	void generateSpeech(void (* callback)(const char*), const char* text, const char* filename = "speech.mp3");

private:

	void processStream(WiFiClient& stream, const char* filename);
	void readUntilQuote(WiFiClient& stream);
};

extern TextToSpeechImpl TextToSpeech;
#endif