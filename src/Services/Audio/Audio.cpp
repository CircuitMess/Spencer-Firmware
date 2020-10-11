#include "Audio.h"
#include <SerialFlash.h>
Audio::Audio()
{
	wav = new AudioGeneratorWAV();
	mp3 = new AudioGeneratorMP3();
	i2s = new I2S();
}

Audio::~Audio()
{
	delete i2s;
	if(file == nullptr) return;
	delete file;
}
void Audio::begin()
{
	out = new AudioOutputI2S(0,0,16,0);
	out->SetRate(16000);
	out->SetPinout(16, 27, 4);
	out->SetChannels(1);
	out->SetOutputModeMono(1);
	out->SetGain(0.1);
	i2s_driver_uninstall(I2S_NUM_0); //revert wrong i2s config from esp8266audio
	i2s->begin();
}
void Audio::record(void (*callback)(void))
{
	recordCallback = callback;

	const int headerSize = 44;
	const int i2sBufferSize = 1600;
	char i2sBuffer[i2sBufferSize];
	char headerData[headerSize];
	float recordLength = 1.0;
	char wavData[i2sBufferSize/4];
	uint wavFileSize = int(recordLength*16000);

	SerialFlash.remove("recording.wav");
	SerialFlash.createErasable("recording.wav", wavFileSize + headerSize);
	SerialFlashFile f = SerialFlash.open("recording.wav");
	f.erase();
	CreateWavHeader((byte*)headerData, wavFileSize);
	f.write(headerData, 44);
	
	if(!i2s->isInited())
	{
		i2s->begin();
	}
	for (uint32_t j = 1; j < wavFileSize/(i2sBufferSize/4); j++) {
		yield();
		i2s->Read(i2sBuffer, i2sBufferSize/2);
		// Serial.println(((int32_t*)i2sBuffer)[0]);
		for (int i = 0; i < i2sBufferSize/8; ++i) {
			yield();
			wavData[2*i] = i2sBuffer[4*i + 2];
			wavData[2*i + 1] = i2sBuffer[4*i + 3];
		}
		f.write(wavData, sizeof(wavData));
	}
	
	f.close();
	recordCallback();
}
void Audio::CreateWavHeader(byte* header, int waveDataSize){
	header[0] = 'R';
	header[1] = 'I';
	header[2] = 'F';
	header[3] = 'F';
	unsigned int fileSizeMinus8 = waveDataSize + 44 - 8;
	header[4] = (byte)(fileSizeMinus8 & 0xFF);
	header[5] = (byte)((fileSizeMinus8 >> 8) & 0xFF);
	header[6] = (byte)((fileSizeMinus8 >> 16) & 0xFF);
	header[7] = (byte)((fileSizeMinus8 >> 24) & 0xFF);
	header[8] = 'W';
	header[9] = 'A';
	header[10] = 'V';
	header[11] = 'E';
	header[12] = 'f';
	header[13] = 'm';
	header[14] = 't';
	header[15] = ' ';
	header[16] = 0x10;  // linear PCM
	header[17] = 0x00;
	header[18] = 0x00;
	header[19] = 0x00;
	header[20] = 0x01;  // linear PCM
	header[21] = 0x00;
	header[22] = 0x01;  // monoral
	header[23] = 0x00;
	header[24] = 0x80;  // sampling rate 16000
	header[25] = 0x3E;
	header[26] = 0x00;
	header[27] = 0x00;
	header[28] = 0x00;  // Byte/sec = 16000x2x1 = 32000
	header[29] = 0x7D;
	header[30] = 0x00;
	header[31] = 0x00;
	header[32] = 0x02;  // 16bit monoral
	header[33] = 0x00;
	header[34] = 0x10;  // 16bit
	header[35] = 0x00;
	header[36] = 'd';
	header[37] = 'a';
	header[38] = 't';
	header[39] = 'a';
	header[40] = (byte)(waveDataSize & 0xFF);
	header[41] = (byte)((waveDataSize >> 8) & 0xFF);
	header[42] = (byte)((waveDataSize >> 16) & 0xFF);
	header[43] = (byte)((waveDataSize >> 24) & 0xFF);
}
void Audio::loop()
{
	if(wav != nullptr)
	{
		if (wav->isRunning()) {
			if (!wav->loop()){
				wav->stop();
				i2s->stop();
			}
		}
	}
	if(mp3 != nullptr)
	{
		if (mp3->isRunning()) {
			if (!mp3->loop()){
				mp3->stop();
				i2s->stop();
			}
		}
	}
}
void Audio::playWAV(AudioFileSource* _file)
{
	if(_file == nullptr) return;
	i2s->begin();
	file = _file;
	wav->begin(file, out);
}
void Audio::playWAV(const char* path)
{
	if(path == nullptr) return;
	i2s->begin();
	file = new AudioFileSourceSerialFlash(path);
	wav->begin(file, out);
}
void Audio::playMP3(AudioFileSource* _file)
{
	if(_file == nullptr) return;
	i2s->begin();
	file = _file;
	if(!mp3->begin(file, out))
	{
		return;
	}
}
void Audio::playMP3(const char* path)
{
	if(path == nullptr) return;
	i2s->begin();
	file = new AudioFileSourceSerialFlash(path);
	mp3->begin(file, out);
}
void Audio::stopPlayback()
{
	if(wav != nullptr)
	{
		if(wav->isRunning()){
			wav->stop();
		}
	}
	if(mp3 != nullptr)
	{
		if(mp3->isRunning()){
			mp3->stop();
		}
	}
	i2s->stop();
}