#ifndef SPENCER_AUDIO_H
#define SPENCER_AUDIO_H

#include "I2S.h"
#include "AudioFileSourceSerialFlash.h"
#include "CompositeAudioFileSource.h"
#include <AudioFileSource.h>
#include <AudioOutputI2S.h>
#include <AudioGeneratorWAV.h>
#include <AudioGeneratorMP3.h>
#include "SampleStore.h"

class Audio
{
public:
	Audio();
	~Audio();
	void begin();
	/**
	 * Starts audio playback.
	 * @param file File to be played.
	 * @param WAVorMP3 Flag to indicate MP3 or wav encoding. True is MP3, false is WAV (also the default).
	 */
	void play(AudioFileSource* file, bool WAVorMP3 = 0);
	/**
	 * Starts audio playback of a file from the serial flash chip.
	 * @param path Path of the file on the flash chip.
	 * @param WAVorMP3 Flag to indicate MP3 or wav encoding. True is MP3, false is WAV (also the default).
	 */
	void play(const char* path, bool WAVorMP3 = 0);
	void stopPlayback();
	/**
	 * Starts audio recording. File is saved on the flash chip as "recording.wav"
	 * @param callback Callback to be executed after done recording.
	 */
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

extern Audio audio;

#endif
