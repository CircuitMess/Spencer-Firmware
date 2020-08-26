#include "AudioFileSourceSerialFlash.h"

AudioFileSourceSerialFlash::AudioFileSourceSerialFlash()
{
}
AudioFileSourceSerialFlash::AudioFileSourceSerialFlash(const char *filename)
{
	open(filename);
}

bool AudioFileSourceSerialFlash::open(const char *filename)
{
	f = SerialFlash.open(filename);
	return f;
}

AudioFileSourceSerialFlash::~AudioFileSourceSerialFlash()
{
	if (f) f.close();
}

uint32_t AudioFileSourceSerialFlash::read(void *data, uint32_t len)
{
	return f.read(reinterpret_cast<uint8_t*>(data), len);
}

bool AudioFileSourceSerialFlash::seek(int32_t pos, int dir)
{
	f.seek(pos); //, (dir==SEEK_SET)?SeekSet:(dir==SEEK_CUR)?SeekCur:SeekEnd);
	return 1;
}

bool AudioFileSourceSerialFlash::close()
{
	f.close();
	return true;
}

bool AudioFileSourceSerialFlash::isOpen()
{
	return f;
}

uint32_t AudioFileSourceSerialFlash::getSize()
{
	if (!f) return 0;
	return f.size();
}
uint32_t AudioFileSourceSerialFlash::getPos()
{
	if (!f) return 0;
	else return f.position(); 
}