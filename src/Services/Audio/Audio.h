#ifndef SPENCER_AUDIO_H
#define SPENCER_AUDIO_H

#include "I2S.h"
#include "AudioFileSourceSerialFlash.h"
#include <AudioFileSource.h>
#include <AudioOutputI2S.h>
#include <AudioGeneratorWAV.h>
#include <AudioGeneratorMP3.h>

class Audio
{
public:
	Audio();
	~Audio();
	void begin();
	void play(AudioFileSource* file);
	void play(const char* path);
	void stopPlayback();
	void record(void (*callback)(void)); // 16bit, monoral, 16000Hz,  linear PCM
	void loop();

private:
	//playback
	I2S* i2s;
	AudioGeneratorWAV *wav = nullptr;
	AudioGeneratorMP3 *mp3;
	AudioOutputI2S *out;
	AudioFileSource *file;

	//recording
	void (*recordCallback)(void) = nullptr;
	static const int headerSize = 44;
	static const int i2sBufferSize = 6000;
	char i2sBuffer[i2sBufferSize];
	void CreateWavHeader(byte* header, int waveDataSize);
	static const int wavDataSize = 60000;                   // It must be multiple of dividedWavDataSize. Recording time is about 1.875s.
	static const int dividedWavDataSize = 1500;
	char** wavData;                                         // It's divided. Because large continuous memory area can't be allocated in esp32.

};


#endif