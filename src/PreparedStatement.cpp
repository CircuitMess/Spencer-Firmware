#include <Loop/LoopManager.h>
#include "PreparedStatement.h"
#include "Speech/TextToSpeech.h"
#include "Services/Audio/AudioFileSourceSerialFlash.h"
#include "Services/Audio/Playback.h"

PreparedStatement::~PreparedStatement(){
	for(const char* filename : files){
		if(filename == nullptr) return;
		TextToSpeech.releaseRecording(filename);
	}
}

void PreparedStatement::addSample(AudioFileSource* sample){
	parts.push_back({ Part::SAMPLE, sample });
}

void PreparedStatement::addTTS(const char* text){
	parts.push_back({ Part::TTS, (void*) text });
}

void PreparedStatement::loop(uint micros){
	for(const char* filename : files){
		if(filename == nullptr) return;
	}

	CompositeAudioFileSource* source = new CompositeAudioFileSource();
	int i = 0;
	for(const Part& part : parts){
		if(part.type == Part::SAMPLE){
			source->add(static_cast<AudioFileSource*>(part.content));
		}else{
			source->add(new AudioFileSourceSerialFlash(files[i++]));
		}
	}

	LoopManager::removeListener(this);
	Playback.playMP3(source);

	if(playbackStarted){
		playbackStarted();
	}
}

void PreparedStatement::play(void (*playbackStarted)()){
	this->playbackStarted = playbackStarted;

	files.reserve(parts.size());

	for(const Part& part : parts){
		if(part.type == Part::TTS){
			files.push_back(nullptr);
			TextToSpeech.addJob({ static_cast<const char*>(part.content), &files.back() });
		}
	}

	LoopManager::addListener(this);
}
