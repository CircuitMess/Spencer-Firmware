#include <sstream>
#include <SerialFlash.h>
#include "TextToSpeech.h"
#include "../Util/Base64Encode.h"
#include "../DataStream/FileReadStream.h"
#include "../DataStream/FileWriteStream.h"
#include "../Util/Base64Decode.h"
#include <ArduinoJson.h>

#define KEY "AIzaSyAQqImCEX2tEnIs-sgEZbcubCeFkTNaIOo"
#define CA "EB:6D:04:1A:C9:07:50:C7:52:C5:BC:69:E0:79:87:A6:5A:E5:2F:A8:23:D7:93:52:8C:9F:E8:62:27:AB:65:47"

TextToSpeechImpl TextToSpeech;

TextToSpeechImpl::TextToSpeechImpl(){

}

void TextToSpeechImpl::generateSpeech(void (* callback)(const char*), const char* text, const char* filename){
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
		callback(nullptr);
		return;
	}

	if(!http.send(reinterpret_cast<uint8_t*>(data), length)){
		Serial.println("Error sending data");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		callback(nullptr);
		return;
	}

	int code = http.finish();
	if(code != 200){
		Serial.printf("HTTP code %d\n", code);
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		callback(nullptr);
		return;
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
		callback(nullptr);
		return;
	}

	callback(filename);
}

void TextToSpeechImpl::processStream(WiFiClient& stream, const char* filename){
	SerialFlash.createErasable(filename, 70000);
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
