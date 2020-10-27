#include "PreparedStatement.h"
#include "Speech/TextToSpeech.h"
#include "Services/Audio/AudioFileSourceSerialFlash.h"

void PreparedStatement::addSample(AudioFileSource* sample){
	parts.push_back({ Part::SAMPLE, sample });
}

void PreparedStatement::addTTS(const char* text){
	parts.push_back({ Part::TTS, (void*) text });
}

CompositeAudioFileSource* PreparedStatement::generate(){
	CompositeAudioFileSource* ret = new CompositeAudioFileSource();

	int recordings = 0;
	char filename[20];
	for(const Part& part : parts){
		if(part.type == Part::SAMPLE){
			ret->add(static_cast<AudioFileSource*>(part.content));
			continue;
		}

		sprintf(filename, "rec-%d.mp3", recordings++);
		TextToSpeech.generateSpeech([](const char* filename){ }, static_cast<const char*>(part.content), filename);
		ret->add(new AudioFileSourceSerialFlash(filename));
	}

	return ret;
}
