#include <sstream>
#include <SerialFlash.h>
#include "TextToSpeech.h"
#include "../DataStream/FileWriteStream.h"
#include "../Util/Base64Decode.h"

#define KEY "AIzaSyAQqImCEX2tEnIs-sgEZbcubCeFkTNaIOo"
#define CA "EE:44:9F:C9:73:17:0C:59:0D:AE:C0:10:A2:77:78:B0:FB:1F:13:01:18:75:2A:35:48:C2:E9:D2:AB:CF:EB:5F"

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
						   "'pitch': 7.2,"
						   "'sampleRateHertz': 16000"
						   "}}";

	char* data = (char*) malloc(sizeof(pattern) + strlen(text) + 2);
	uint length = sprintf(data, pattern, text);

	StreamableHTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	http.begin("https://spencer.circuitmess.com:8443/tts/v1/text:synthesize", CA);
	http.addHeader("Key", KEY);
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
