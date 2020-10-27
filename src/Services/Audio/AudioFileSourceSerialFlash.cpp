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
	while(!SerialFlash.ready());
	f = SerialFlash.open(filename);
	
	if(!f) f.close();
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
	if((dir == SEEK_CUR && pos > (f.size() - 1 - getPos())) || (pos > (f.size() - 1))) return false;
	switch (dir)
	{
	case SEEK_SET:
		f.seek(pos);
		break;
	case SEEK_END:
		f.seek(f.size() - 1);
		break;
	case SEEK_CUR:
		f.seek(pos + getPos());
		break;
	}
	return true;
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