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
#include <Loop/LoopListener.h>

class AudioImpl : public LoopListener
{
public:
	AudioImpl();
	~AudioImpl();
	void begin(I2S* i2s);
	/**
	 * Starts WAV audio playback from an AudioFileSource pointer.
	 * @param file AudioFileSource pointer to the desired file.
	 */
	void playWAV(AudioFileSource* file);
	/**
	 * Starts WAV audio playback of a file from the serial flash chip.
	 * @param path Path of the file on the flash chip.
	 */
	void playWAV(const char* path);
	/**
	 * Starts MP3 audio playback from an AudioFileSource pointer.
	 * @param file AudioFileSource pointer to the desired file.
	 */
	void playMP3(AudioFileSource* file);
	/**
	 * Starts MP3 audio playback of a file from the serial flash chip.
	 * @param path Path of the file on the flash chip.
	 */
	void playMP3(const char* path);
	void stopPlayback();

	void loop(uint _time) override;
	bool isRunning();

private:
	I2S* i2s;
	AudioGeneratorWAV *wav = nullptr;
	AudioGeneratorMP3 *mp3;
	AudioOutputI2S *out;
	AudioFileSource *file;

};

extern AudioImpl Audio;

#endif
