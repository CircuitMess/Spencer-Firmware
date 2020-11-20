#include "CompositeAudioFileSource.h"
CompositeAudioFileSource::CompositeAudioFileSource(){

}

CompositeAudioFileSource::CompositeAudioFileSource(AudioFileSource* file) : CompositeAudioFileSource(){
	add(file);
}

CompositeAudioFileSource::~CompositeAudioFileSource()
{
	for (auto file : filePointers){
		if(file != nullptr){
			file->close();
			delete file;
		}
	}
}

void CompositeAudioFileSource::add(AudioFileSource* file)
{
	filePointers.push_back(file);
	file->seek(0, SEEK_SET);
	size+=file->getSize();
}
AudioFileSource* CompositeAudioFileSource::getCurrentFile()
{
	if(currentFileIndex >= filePointers.size()) return nullptr;
	return filePointers[currentFileIndex];
}

bool CompositeAudioFileSource::open(const char *filename)
{
	return true; //files should already be opened before being added
}

uint32_t CompositeAudioFileSource::read(void *data, uint32_t len)
{
	int readBytes = getCurrentFile()->read(reinterpret_cast<uint8_t*>(data), len);
	if(readBytes == 0 && currentFileIndex < filePointers.size() - 1)
	{
		currentFileIndex++;
		getCurrentFile()->seek(0, SEEK_SET);
		
		readBytes = getCurrentFile()->read(reinterpret_cast<uint8_t*>(data), len);
	}
	return readBytes;
}

bool CompositeAudioFileSource::seek(int32_t pos, int dir)
{
	if(dir == SEEK_CUR && pos > (size - 1)) return false;
	switch (dir)
	{
	case SEEK_SET:
		currentFileIndex = 0;
		getCurrentFile()->seek(0, SEEK_SET);
		break;
	case SEEK_END:
		currentFileIndex = filePointers.size() - 1;
		getCurrentFile()->seek(getCurrentFile()->getSize() - 1, SEEK_END);
		break;
	default:
		int fileIndex = 0;
		while (pos >= 0)
		{
			pos-=filePointers[fileIndex]->getSize();
			fileIndex++;
		}
		fileIndex--;
		currentFileIndex = fileIndex;
		getCurrentFile()->seek(pos, SEEK_CUR);
		break;
	}
	return true;
}

bool CompositeAudioFileSource::close()
{
	for (auto file : filePointers)
	{
		if(file != nullptr){
			file->close();
		}
	}
}

bool CompositeAudioFileSource::isOpen()
{
	return getCurrentFile()->isOpen();
}

uint32_t CompositeAudioFileSource::getSize()
{
	return size;
}
uint32_t CompositeAudioFileSource::getPos()
{
	size_t pos = 0;
	for(size_t i = 0; i < currentFileIndex; i++)
	{
		pos+=filePointers[currentFileIndex]->getSize();
	}
	pos+=getCurrentFile()->getPos();
	return pos;
}