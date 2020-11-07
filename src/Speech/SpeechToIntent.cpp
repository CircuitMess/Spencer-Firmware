#include <SerialFlash.h>
#include <ArduinoJson.h>
#include "SpeechToIntent.h"
#include "../Util/Base64Encode.h"
#include "../DataStream/FileReadStream.h"
#include "../Util/StreamableHTTPClient.h"

#define KEY "AIzaSyCHrLm1YLWFO1UpDEaaiIdJtm49aVODfDE"
#define CA "DC:03:B5:D6:0C:F1:02:F1:B1:D0:62:27:9F:3E:B4:C3:CD:C9:93:BA:20:65:6D:06:DC:5D:56:AC:CC:BA:40:20"

SpeechToIntentImpl SpeechToIntent;

SpeechToIntentImpl::SpeechToIntentImpl() : AsyncProcessor("STI_Job"){

}

void SpeechToIntentImpl::doJob(const STIJob& job){
	*job.result = identifyVoice(job.recordingFilename);
}

IntentResult* SpeechToIntentImpl::identifyVoice(const char* filename){
	const char prefix[] = "{"
						  "'config': {"
						  "'sampleRateHertz': 16000,"
						  "'languageCode': 'en-US',"
						  "'enableWordTimeOffsets': false"
						  "}, 'audio': { 'content': '";
	const char suffix[] = "' }}";

	SerialFlashFile file = SerialFlash.open(filename);
	if(!file){
		Serial.println("Couldn't open file for reading");
		return nullptr;
	}

	int wavSize = 0;
	file.seek(4); //skip RIFF on start of file
	for(int8_t i = 0; i < 4; i++)
	{
		file.read(&(((char*)(void*)&wavSize)[i]), 1);
		Serial.println((((char*)(void*)&wavSize)[i]), BIN);
	}
	wavSize+=8;
	file.seek(0);

	FileReadStream fileStream(&file);
	Base64Encode encodeStream(&fileStream);

	StreamableHTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	http.begin("https://spencer.circuitmess.com:8443/stt/v1/speech:recognize", CA);
	http.addHeader("Key", KEY);
	http.addHeader("Content-Type", "application/json; charset=utf-8");
	http.addHeader("Accept-Encoding", "identity");

	uint length = sizeof(prefix) + sizeof(suffix) + ceil((float) wavSize * (4.0f / 3.0f)) + 20;
	http.addHeader("Content-Length", String(length));

	if(!http.startPOST()){
		Serial.println("Error connecting");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return nullptr;
	}

	if(!http.send((uint8_t*) prefix, sizeof(prefix) - 1)){
		Serial.println("Error sending prefix");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return nullptr;
	}

	uint sent = 0;
	auto sendFunc = [&http, &sent](unsigned char byte){
		if(!http.send(&byte, 1)){
			Serial.println("Error sending data");
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return nullptr;
		}
		sent += 1;
	};

	for(uint i = 0; i < wavSize; i++){
		if(!encodeStream.available()) break;
		sendFunc(encodeStream.get());
	}

	file.seek(file.size());

	while(encodeStream.available()){
		sendFunc(encodeStream.get());
	}

	if(!http.send((uint8_t*) suffix, sizeof(suffix) - 1)){
		Serial.println("Error sending suffix");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return nullptr;
	}

	sent += sizeof(prefix) - 1;
	sent += sizeof(suffix) - 1;

	unsigned char nl = '\n';
	while(sent < length){
		if(!http.send(&nl, 1)){
			Serial.println("Error sending trailer");
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return nullptr;
		}

		sent++;
	}

	int code = http.finish();
	if(code != 200){
		Serial.printf("HTTP code %d\n", code);
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return nullptr;
	}

	const int SIZE = 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(6) + 200;
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, http.getStream());

	http.end();
	http.getStream().stop();
	http.getStream().flush();

	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		return nullptr;
	}

	if(!json.containsKey("transcript")){
		Serial.println("Failed recognizing");
		return nullptr;
	}

	IntentResult* result = new IntentResult;
	result->transcript = json["transcript"].as<const char*>();
	result->intent = json["intent"]["result"].as<const char*>();
	result->confidence = json["intent"]["confidence"].as<float>();

	return result;
}
