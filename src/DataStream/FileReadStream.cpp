#include <queue>
#include "FileReadStream.h"

FileReadStream::FileReadStream(SerialFlashFile source) : source(source){
	buffer.reserve(bufferSize);
}

bool FileReadStream::available(){
	return !buffer.empty() || source.position() < source.size();
}

unsigned char FileReadStream::get(){
	if(buffer.empty()){
		buffer.resize(bufferSize);
		source.read(buffer.data(), buffer.size());
	}

	if(buffer.empty()) return 0;

	// TODO: Vector is a bad data structure for this. Should use a queue instead
	unsigned char byte = buffer.front();
	buffer.erase(buffer.begin());
	return byte;
}
