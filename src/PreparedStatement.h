#ifndef SPENCER_PREPAREDSTATEMENT_H
#define SPENCER_PREPAREDSTATEMENT_H

#include <vector>
#include <AudioFileSource.h>
#include "Services/Audio/CompositeAudioFileSource.h"
#include <Loop/LoopListener.h>

class PreparedStatement : public LoopListener {
public:
	virtual ~PreparedStatement();

	void addSample(AudioFileSource* sample);

	void addTTS(const char* text);

	void play(void (*playbackStarted)());
	void loop(uint micros) override;

private:
	struct Part {
		enum { SAMPLE, TTS } type;
		void* content;
	};

	std::vector<Part> parts;
	std::vector<const char*> files;

	void (*playbackStarted)() = nullptr;
};


#endif //SPENCER_PREPAREDSTATEMENT_H
