#ifndef SPENCER_RECORDING_H
#define SPENCER_RECORDING_H


#include "I2S.h"

class SerialFlashFile;

class RecordingImpl {
public:

	/**
	 * Starts audio recording. File is saved on the flash chip as "recording.wav"
	 * @param callback Callback to be executed after done recording.
	 */
	void record(void (*callback)(void)); // 16bit, monoral, 16000Hz,  linear PCM

	void begin(I2S* i2s);

private:
	const uint16_t wavHeaderSize = 44;
	const uint32_t i2sBufferSize = 1600;
	const uint32_t sampleRate = 16000;
	const float maxRecordTime = 3.0f; // in seconds
	const float cutoffThreshold = 0.5f;
	const float cutoffTime = 1.0f; // in seconds, time where amplitude is below max*cutoffThreshold before recording is cut
#define avgBufferSize 10

	I2S* i2s = nullptr;

	void writeWavHeader(SerialFlashFile* file, int wavSize);
	void compress(const char* inputFilename, const char* outputFilename, size_t wavSize);
};

extern RecordingImpl Recording;

#endif //SPENCER_RECORDING_H
