#include "Audio.h"
#include "Compression.h"
#include <SerialFlash.h>
AudioImpl Audio;
AudioImpl::AudioImpl()
{
	wav = new AudioGeneratorWAV();
	mp3 = new AudioGeneratorMP3();
	i2s = new I2S();
}

AudioImpl::~AudioImpl()
{
	delete i2s;
	if(file == nullptr) return;
	delete file;
}
void AudioImpl::begin()
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
void AudioImpl::record(void (*callback)(void))
{

	const uint32_t wavBufferSize = sizeof(int16_t) * i2sBufferSize / 4; // i2sBuffer is stereo by byte, wavBuffer is mono int16
	const uint32_t noReadings = (maxRecordTime * sampleRate * 4) / i2sBufferSize; // time * sampleRate * 4 bytes per sample (sample is int16_t, 2 channels)

	char* i2sBuffer = static_cast<char*>(malloc(i2sBufferSize));
	int16_t* wavBuffer = static_cast<int16_t*>(malloc(wavBufferSize));
	const uint wavFileSize = maxRecordTime * (float) sampleRate * 2.0f;

	SerialFlash.createErasable("recordingRaw.wav", wavFileSize + wavHeaderSize);
	SerialFlashFile file = SerialFlash.open("recordingRaw.wav");
	file.erase();
	file.seek(wavHeaderSize);
	
	if(!i2s->isInited()){
		i2s->begin();
	}

	uint16_t ampBuffer[avgBufferSize] = {0};
	uint16_t ampPointer = 0;
	uint16_t maxAmp = 0;
	bool underMax = false;
	uint underMaxTime = 0;
	uint32_t wavTotalWritten = 0;

	for(int i = 0; i < noReadings; i++){
		i2s->Read(i2sBuffer, i2sBufferSize);

		for(int j = 0; j < i2sBufferSize; j += 4){
			int16_t sample = *(int16_t*)(&i2sBuffer[j + 2]) + 3705;
			wavBuffer[j/4] = sample;

			ampBuffer[ampPointer++] = abs(sample);
			if(ampPointer == avgBufferSize){
				ampPointer = 0;
			}

			uint32_t sum = 0;
			for(int k = 0; k < avgBufferSize; k++) sum += ampBuffer[k];
			uint16_t avgLastN = sum / avgBufferSize;
			maxAmp = max(maxAmp, avgLastN);

			if(abs(sample) < (float) maxAmp * cutoffThreshold){
				if(!underMax){
					underMax = true;
					underMaxTime = millis();
				}
			}else if(underMax){
				underMax = false;
			}

		}

		file.write(wavBuffer, wavBufferSize);
		wavTotalWritten += wavBufferSize;
		if(underMax && (millis() - underMaxTime) >= cutoffTime * 1000){
			break;
		}
	}

	file.seek(0);
	writeWavHeader(&file, wavTotalWritten);
	file.close();

	free(i2sBuffer);
	free(wavBuffer);

	compress("recordingRaw.wav", "recording.wav", wavTotalWritten);

	callback();
}

void Audio::compress(const char* inputFilename, const char* outputFilename, size_t wavSize){
	SerialFlashFile input = SerialFlash.open(inputFilename);
	if(!input){
		Serial.println("Failed opening input file");
		return;
	}

	SerialFlash.createErasable(outputFilename, maxRecordTime * (float) sampleRate * 2.0f + wavHeaderSize);
	SerialFlashFile output = SerialFlash.open(outputFilename);
	output.erase();
	if(!output){
		Serial.println("Failed opening output file");
		return;
	}

	writeWavHeader(&output, wavSize);
	input.seek(wavHeaderSize);

	const uint16_t samplesPerProcess = 32 * 100;

	Compression comp(16000, 10, 5, -26, 5, 5, 0.003f, 0.250f);
	int16_t* inputBuf = static_cast<int16_t*>(malloc(sizeof(int16_t) * samplesPerProcess));
	int16_t* outputBuf = static_cast<int16_t*>(malloc(sizeof(int16_t) * samplesPerProcess));

	size_t totalProcessed = 0;
	while(input.read(inputBuf, samplesPerProcess * sizeof(int16_t))){
		comp.process(inputBuf, outputBuf, samplesPerProcess);
		output.write(outputBuf, samplesPerProcess * sizeof(int16_t));

		totalProcessed += samplesPerProcess * sizeof(int16_t);
		if(totalProcessed >= wavSize) break;
	}

	input.close();
	output.close();
	free(inputBuf);
	free(outputBuf);
}

void Audio::writeWavHeader(SerialFlashFile* file, int wavSize){
	unsigned char header[wavHeaderSize];
	unsigned int fileSizeMinus8 = wavSize + 44 - 8;
	header[0] = 'R';
	header[1] = 'I';
	header[2] = 'F';
	header[3] = 'F';
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
	header[40] = (byte)(wavSize & 0xFF);
	header[41] = (byte)((wavSize >> 8) & 0xFF);
	header[42] = (byte)((wavSize >> 16) & 0xFF);
	header[43] = (byte)((wavSize >> 24) & 0xFF);

	file->write(header, sizeof(header));
}
void AudioImpl::loop()
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
void AudioImpl::playWAV(AudioFileSource* _file)
{
	if(_file == nullptr) return;
	i2s->begin();
	file = _file;
	wav->begin(file, out);
}
void AudioImpl::playWAV(const char* path)
{
	if(path == nullptr) return;
	i2s->begin();
	file = new AudioFileSourceSerialFlash(path);
	wav->begin(file, out);
}
void AudioImpl::playMP3(AudioFileSource* _file)
{
	if(_file == nullptr) return;
	i2s->begin();
	file = _file;
	if(!mp3->begin(file, out))
	{
		return;
	}
}
void AudioImpl::playMP3(const char* path)
{
	if(path == nullptr) return;
	i2s->begin();
	file = new AudioFileSourceSerialFlash(path);
	mp3->begin(file, out);
}
void AudioImpl::stopPlayback()
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