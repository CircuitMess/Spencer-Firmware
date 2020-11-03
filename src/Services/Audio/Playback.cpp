#include "Playback.h"
#include "Compression.h"
#include <SerialFlash.h>
PlaybackImpl Playback;
PlaybackImpl::PlaybackImpl()
{
	wav = new AudioGeneratorWAV();
	mp3 = new AudioGeneratorMP3();
	i2s = new I2S();
}

PlaybackImpl::~PlaybackImpl()
{
	if(file == nullptr) return;
	delete file;
}
void PlaybackImpl::begin(I2S* i2s)
{
	this->i2s = i2s;
	out = new AudioOutputI2S(0,0,16,0);
	out->SetRate(16000);
	out->SetPinout(16, 27, 4);
	out->SetChannels(1);
	out->SetOutputModeMono(1);
	out->SetGain(0.1);
}
void PlaybackImpl::loop(uint _time)
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
void PlaybackImpl::playWAV(AudioFileSource* _file)
{
	if(_file == nullptr) return;
	i2s->begin();
	file = _file;
	wav->begin(file, out);
}
void PlaybackImpl::playWAV(const char* path)
{
	if(path == nullptr) return;
	i2s->begin();
	file = new AudioFileSourceSerialFlash(path);
	wav->begin(file, out);
}
void PlaybackImpl::playMP3(AudioFileSource* _file)
{
	if(_file == nullptr) return;
	i2s->begin();
	file = _file;
	if(!mp3->begin(file, out))
	{
		return;
	}
}
void PlaybackImpl::playMP3(const char* path)
{
	if(path == nullptr) return;
	i2s->begin();
	file = new AudioFileSourceSerialFlash(path);
	mp3->begin(file, out);
}
void PlaybackImpl::stopPlayback()
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
bool PlaybackImpl::isRunning()
{
	return i2s->isInited();
}