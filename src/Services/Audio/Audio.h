#ifndef SPENCER_AUDIO_H
#define SPENCER_AUDIO_H

#include "I2S.h"
#include "AudioFileSourceSerialFlash.h"
#include "AudioFileSourceRAM.h"
class Audio
{
public:
	Audio();
	~Audio();
	void begin();
	// 16bit, monoral, 16000Hz,  linear PCM
	void record(void (*callback)(byte*, size_t));
private:
	void (*recordCallback)(byte*, size_t) = nullptr;

	I2S* i2s;
	static const int headerSize = 44;
	static const int i2sBufferSize = 6000;
	char i2sBuffer[i2sBufferSize];
	void CreateWavHeader(byte* header, int waveDataSize);

	static const int wavDataSize = 60000;                   // It must be multiple of dividedWavDataSize. Recording time is about 1.875s.
	static const int dividedWavDataSize = i2sBufferSize/4;
	char** wavData;                                         // It's divided. Because large continuous memory area can't be allocated in esp32.
	// byte paddedHeader[headerSize + 4] = {0};                // The size must be multiple of 3 for Base64 encoding. Additional byte size must be even because wave data is 16bit.

};


#endif