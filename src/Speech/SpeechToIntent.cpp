#include <SerialFlash.h>
#include <ArduinoJson.h>
#include "SpeechToIntent.h"
#include "../Util/Base64Encode.h"
#include "../DataStream/FileReadStream.h"
#include "../Util/StreamableHTTPClient.h"
#include "../Net.h"
#include "../Settings.h"

#define CA "DC:03:B5:D6:0C:F1:02:F1:B1:D0:62:27:9F:3E:B4:C3:CD:C9:93:BA:20:65:6D:06:DC:5D:56:AC:CC:BA:40:20"

SpeechToIntentImpl SpeechToIntent;

IntentResult::IntentResult(Error error) : error(error), entities({}){
	if(error != OK){
		intent = transcript = nullptr;
		confidence = 0;
	}
}

IntentResult::~IntentResult(){
	delete transcript;
	delete intent;
}

SpeechToIntentImpl::SpeechToIntentImpl() : AsyncProcessor("STI_Job"){

}

void SpeechToIntentImpl::doJob(const STIJob& job){
	if(!Net.checkConnection() && !Net.reconnect()){
		*job.result = new IntentResult(IntentResult::NETWORK);
		return;
	}

	IntentResult* result = identifyVoice(job.recordingFilename);

	*job.result = result;
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
		return new IntentResult(IntentResult::FILE);
	}

	uint wavSize = 0;
	file.seek(4); //skip RIFF on start of file
	for(int8_t i = 0; i < 4; i++){
		file.read(&(((char*)(void*)&wavSize)[i]), 1);
	}
	wavSize+=8;
	file.seek(0);

	uint wavSendSize = ceil((float) wavSize * (4.0f / 3.0f)) + 8;

	FileReadStream fileStream(&file);
	Base64Encode encodeStream(&fileStream);

	StreamableHTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	if(!http.begin("https://spencer.circuitmess.com:8443/stt/v1/speech:recognize", CA)){
		return new IntentResult(IntentResult::NETWORK);
	}

	http.addHeader("Key", Settings.get().google_key);
	http.addHeader("Content-Type", "application/json; charset=utf-8");
	http.addHeader("Accept-Encoding", "identity");

	uint length = sizeof(prefix) + sizeof(suffix) + wavSendSize + 8;
	http.addHeader("Content-Length", String(length));

	if(!http.startPOST()){
		Serial.println("Error connecting");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(IntentResult::NETWORK);
	}

	if(!http.send((uint8_t*) prefix, sizeof(prefix) - 1)){
		Serial.println("Error sending prefix");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(IntentResult::NETWORK);
	}

	uint sent = 0;
	auto sendFunc = [&http, &sent](unsigned char byte) -> bool {
		if(!http.send(&byte, 1)){
			Serial.println("Error sending data");
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return false;
		}

		sent += 1;
		return true;
	};

	for(uint i = 0; i < wavSendSize; i++){
		if(!encodeStream.available()) break;
		if(!sendFunc(encodeStream.get())){
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return new IntentResult(IntentResult::NETWORK);
		}
	}

	file.seek(file.size());
	fileStream.clearBuffer();

	while(encodeStream.available()){
		if(!sendFunc(encodeStream.get())){
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return new IntentResult(IntentResult::NETWORK);
		}
	}

	if(!http.send((uint8_t*) suffix, sizeof(suffix) - 1)){
		Serial.println("Error sending suffix");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(IntentResult::NETWORK);
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
			return new IntentResult(IntentResult::NETWORK);
		}

		sent++;
	}

	int code = http.finish();
	if(code != 200){
		Serial.printf("HTTP code %d\n", code);
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(code == 400 ? IntentResult::KEY : IntentResult::NETWORK);
	}

	const int SIZE = JSON_ARRAY_SIZE(2) + 4 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 200;
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, http.getStream());

	http.end();
	http.getStream().stop();
	http.getStream().flush();

	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		return new IntentResult(IntentResult::JSON);
	}

	if(!json.containsKey("transcript")){
		Serial.println("Failed recognizing speech");
		return new IntentResult(IntentResult::INTENT);
	}

	const char* intent = json["intent"]["result"].as<const char*>();
	if(intent[0] == '\0'){
		Serial.println("Failed recognizing intent");
		return new IntentResult(IntentResult::INTENT);
	}

	IntentResult* result = new IntentResult(IntentResult::OK);
	result->confidence = json["intent"]["confidence"].as<float>();

	const char* transcript = json["transcript"].as<const char*>();
	uint32_t transcriptLength = strlen(transcript);
	result->transcript = static_cast<char*>(malloc(transcriptLength + 1));
	memset(result->transcript, 0, transcriptLength+1);
	memcpy(result->transcript, transcript, transcriptLength);

	uint32_t intentLength = strlen(intent);
	result->intent = static_cast<char*>(malloc(intentLength + 1));
	memset(result->intent, 0, intentLength+1);
	memcpy(result->intent, intent, intentLength);

	if(!json.containsKey("entities")) return result;

	uint noEntities = json["entities"].size();
	for(int i = 0; i < noEntities; i++){
		auto entity = json["entities"].getElement(i);
		if(!entity.containsKey("slot") || !entity.containsKey("value")) continue;

		std::string slot = entity["slot"].as<std::string>();
		std::string value = entity["value"].as<std::string>();

		if(result->entities.find(slot) != result->entities.end()) continue;

		result->entities.insert(std::pair<std::string, std::string>(slot, value));
	}

	return result;
}
