#ifndef SPENCER_PREPAREDSTATEMENT_H
#define SPENCER_PREPAREDSTATEMENT_H

#include <Util/Vector.h>
#include <AudioFileSource.h>
#include "Services/Audio/CompositeAudioFileSource.h"

class PreparedStatement {
public:
	void addSample(AudioFileSource* sample);
	void addTTS(const char* text);

	CompositeAudioFileSource* generate();

private:
	struct Part {
		enum { SAMPLE, TTS } type;
		void* content;
	};

	Vector<Part> parts;

};


#endif //SPENCER_PREPAREDSTATEMENT_H
