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

	StreamableHTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	if(!http.begin("https://spencer.circuitmess.com:8443/sti/speech", CA)){
		return new IntentResult(IntentResult::NETWORK);
	}

	http.addHeader("Content-Type", "audio/wav");
	http.addHeader("Accept-Encoding", "identity");
	http.addHeader("Content-Length", String(wavSize));


	if(!http.startPOST()){
		Serial.println("Error connecting");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(IntentResult::NETWORK);
	}

	uint sent = 0;
	unsigned char buffer[256];
	while(sent < wavSize){
		uint readSize = min((uint) 256, wavSize - sent);
		file.read(buffer, readSize);
		if(!http.send(buffer, readSize)){
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return new IntentResult(IntentResult::NETWORK);
		}
		sent += readSize;
	}


	int code = http.finish();
	if(code != 200){
		Serial.printf("HTTP code %d\n", code);
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(IntentResult::JSON);
	}

	const int SIZE = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(50) + 200;
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

	if(!json.containsKey("text") || !json.containsKey("intents") || json["intents"].size() == 0){
		return new IntentResult(IntentResult::INTENT);
	}

	const char* intent = json["intents"][0]["name"].as<const char*>();
	if(intent[0] == '\0'){
		return new IntentResult(IntentResult::INTENT);
	}

	IntentResult* result = new IntentResult(IntentResult::OK);
	result->confidence = json["intents"][0]["confidence"].as<float>();

	uint32_t intentLength = strlen(intent);
	result->intent = static_cast<char*>(malloc(intentLength + 1));
	memset(result->intent, 0, intentLength+1);
	memcpy(result->intent, intent, intentLength);

	const char* transcript = json["text"].as<const char*>();
	uint32_t transcriptLength = strlen(transcript);
	result->transcript = static_cast<char*>(malloc(transcriptLength + 1));
	memset(result->transcript, 0, transcriptLength+1);
	memcpy(result->transcript, transcript, transcriptLength);

	if(!json.containsKey("entities")) return result;

	for(const auto& entityObj : json["entities"].as<JsonObject>()){
		auto entityArr = entityObj.value().as<JsonArray>();
		if(entityArr.size() == 0) continue;
		auto entity = entityArr[0];

		if(!entity.containsKey("name") || !entity.containsKey("body")) continue;

		std::string slot = entity["name"].as<std::string>();
		std::string value = entity["body"].as<std::string>();

		if(result->entities.find(slot) != result->entities.end()) continue;

		result->entities.insert(std::pair<std::string, std::string>(slot, value));
	}

	return result;
}
