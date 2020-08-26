#ifndef SPENCER_AUDIOFILESOURCESERIALFLASH_H
#define SPENCER_AUDIOFILESOURCESERIALFLASH_H

#include <AudioFileSource.h>
#include <SerialFlash.h>


class AudioFileSourceSerialFlash : public AudioFileSource
{
public:
	AudioFileSourceSerialFlash();
	AudioFileSourceSerialFlash(const char *filename);
	virtual ~AudioFileSourceSerialFlash() override;
	
	virtual bool open(const char *filename) override;
	virtual uint32_t read(void *data, uint32_t len) override;
	virtual bool seek(int32_t pos, int dir) override;
	virtual bool close() override;
	virtual bool isOpen() override;
	virtual uint32_t getSize() override;
	virtual uint32_t getPos() override;

private:
	SerialFlashFile f;
};


#endif