#include <sstream>
#include <SerialFlash.h>
#include "TextToSpeech.h"
#include "../DataStream/FileWriteStream.h"
#include "../Util/Base64Decode.h"
#include "../Settings.h"

#define CA "DC:03:B5:D6:0C:F1:02:F1:B1:D0:62:27:9F:3E:B4:C3:CD:C9:93:BA:20:65:6D:06:DC:5D:56:AC:CC:BA:40:20"

const char* stash[] = {
		"recording-1.mp3",
		"recording-2.mp3",
		"recording-3.mp3",
		"recording-4.mp3"
};

#define STASH_COUNT (sizeof(stash) / sizeof(stash[0]))

TextToSpeechImpl TextToSpeech;

TextToSpeechImpl::TextToSpeechImpl() : AsyncProcessor("TTS_Task", STASH_COUNT), fileStash(::stash, ::stash + STASH_COUNT){

}

void TextToSpeechImpl::releaseRecording(const char* filename){
	stashMut.lock();
	fileStash.insert(filename);
	stashMut.unlock();
}

void TextToSpeechImpl::doJob(const TTSJob& job){
	stashMut.lock();
	const char* filename = *fileStash.begin();
	fileStash.erase(filename);
	stashMut.unlock();

	*job.resultFilename = generateSpeech(job.text, filename);
}

const char* TextToSpeechImpl::generateSpeech(const char* text, const char* filename){
	const char pattern[] = "{ 'input': { 'text': '%s' },"
						   "'voice': {"
						   "'languageCode': 'en-US',"
						   "'name': 'en-US-Standard-D',"
						   "'ssmlGender': 'NEUTRAL'"
						   "}, 'audioConfig': {"
						   "'audioEncoding': 'MP3',"
						   "'speakingRate': 0.96,"
						   "'pitch': 5.5,"
						   "'sampleRateHertz': 16000"
						   "}}";

	char* data = (char*) malloc(sizeof(pattern) + strlen(text) + 2);
	uint length = sprintf(data, pattern, text);

	StreamableHTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	http.begin("https://spencer.circuitmess.com:8443/tts/v1/text:synthesize", CA);
	http.addHeader("Key", "Foo");
	http.addHeader("Content-Type", "application/json; charset=utf-8");
	http.addHeader("Accept-Encoding", "identity");
	http.addHeader("Content-Length", String(length));

	if(!http.startPOST()){
		Serial.println("Error connecting");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return nullptr;
	}

	if(!http.send(reinterpret_cast<uint8_t*>(data), length)){
		Serial.println("Error sending data");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return nullptr;
	}

	int code = http.finish();
	if(code != 200){
		Serial.printf("HTTP code %d\n", code);
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return nullptr;
	}

	enum { PRE, PROP, VAL, POST } state = PRE;
	WiFiClient& stream = http.getStream();
	bool processed = false;

	while(stream.available()){
		if(state == PRE){
			readUntilQuote(stream);
			state = PROP;
		}else if(state == PROP){
			String prop = stream.readStringUntil('"');
			if(prop.equals("audioContent")){
				readUntilQuote(stream);
				state = VAL;
			}else{
				readUntilQuote(stream);
				readUntilQuote(stream);
				state = PRE;
			}
		}else if(state == VAL){
			processStream(stream, filename);
			processed = true;
			break;
		}
	}

	http.end();
	stream.stop();
	stream.flush();

	if(!processed){
		Serial.println("Error processing stream");
		return nullptr;
	}

	return filename;
}

void TextToSpeechImpl::processStream(WiFiClient& stream, const char* filename){
	SerialFlash.createErasable(filename, 64000);
	SerialFlashFile file = SerialFlash.open(filename);
	file.erase();

	FileWriteStream fileStream(file);
	Base64Decode decodeStream(&fileStream);

	unsigned char byte;
	int status;
	while(stream.available() && (status = stream.read(&byte, 1)) && byte != '"'){
		if(status != 1) continue;
		if(byte == '\n') continue;
		decodeStream.write(byte);
	}

	fileStream.flush();
	file.close();
}

void TextToSpeechImpl::readUntilQuote(WiFiClient& stream){
	unsigned char byte;
	while(stream.available() && stream.read(&byte, 1) && byte != '"');
}
