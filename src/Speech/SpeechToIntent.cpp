#include <SerialFlash.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "SpeechToIntent.h"
#include "../Util/Base64Encode.h"
#include "../DataStream/FileReadStream.h"
#include "../Util/StreamableHTTPClient.h"
#include "../Net.h"

#define KEY "AIzaSyCHrLm1YLWFO1UpDEaaiIdJtm49aVODfDE"
#define CA "DC:03:B5:D6:0C:F1:02:F1:B1:D0:62:27:9F:3E:B4:C3:CD:C9:93:BA:20:65:6D:06:DC:5D:56:AC:CC:BA:40:20"

SpeechToIntentImpl SpeechToIntent;

SpeechToIntentImpl::SpeechToIntentImpl() : AsyncProcessor("STI_Job"){

}

void SpeechToIntentImpl::doJob(const STIJob& job){
	if(!Net.checkConnection() && !Net.reconnect()){
		*job.result = new IntentResult{ IntentResult::NETWORK, nullptr, nullptr, 0 };
		return;
	}

	IntentResult* result = identifyVoice(job.recordingFilename);

	if(result->error != IntentResult::OK){
		result->intent = result->transcript = nullptr;
		result->confidence = 0;
	}

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
		return new IntentResult { IntentResult::FILE };
	}

	int wavSize = 0;
	file.seek(4); //skip RIFF on start of file
	for(int8_t i = 0; i < 4; i++){
		file.read(&(((char*)(void*)&wavSize)[i]), 1);
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
		return new IntentResult { IntentResult::NETWORK };
	}

	if(!http.send((uint8_t*) prefix, sizeof(prefix) - 1)){
		Serial.println("Error sending prefix");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult { IntentResult::NETWORK };
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

	for(uint i = 0; i < wavSize; i++){
		if(!encodeStream.available()) break;
		if(!sendFunc(encodeStream.get())){
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return new IntentResult { IntentResult::NETWORK };
		}
	}

	file.seek(file.size());

	while(encodeStream.available()){
		if(!sendFunc(encodeStream.get())){
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return new IntentResult { IntentResult::NETWORK };
		}
	}

	if(!http.send((uint8_t*) suffix, sizeof(suffix) - 1)){
		Serial.println("Error sending suffix");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult { IntentResult::NETWORK };
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
			return new IntentResult { IntentResult::NETWORK };
		}

		sent++;
	}

	int code = http.finish();
	if(code != 200){
		Serial.printf("HTTP code %d\n", code);
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult { IntentResult::NETWORK };
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
		return new IntentResult { IntentResult::JSON };
	}

	if(!json.containsKey("transcript")){
		Serial.println("Failed recognizing");
		return new IntentResult { IntentResult::INTENT };
	}

	// TODO: provjerit dal se vrši prijenos vlasništva
	IntentResult* result = new IntentResult;
	result->error = IntentResult::OK;
	result->transcript = json["transcript"].as<const char*>();
	result->intent = json["intent"]["result"].as<const char*>();
	result->confidence = json["intent"]["confidence"].as<float>();

	if(result->intent[0] == '\0') result->intent = "none";

	return result;
}
