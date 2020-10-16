#include <string>
#include "Base64Decode.h"

static const std::string base64table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/.";

Base64Decode::Base64Decode(WriteStream* destination) : destination(destination){
	buffer.reserve(4);
}

void Base64Decode::write(unsigned char byte){
	buffer.push_back(byte);

	if(buffer.size() == 4){
		writeBuffer();
		buffer.clear();
	}
}

void Base64Decode::writeBuffer(){
	uint i1 = base64table.find(buffer[0]);
	uint i2 = base64table.find(buffer[1]);
	destination->write((i1 << 2) + ((i2 & 0x30) >> 4));

	if(buffer[2] == '=') return;
	uint i3 = base64table.find(buffer[2]);
	destination->write(((i2 & 0x0f) << 4) + ((i3 & 0x3c) >> 2));

	if(buffer[3] == '=') return;
	uint i4 = base64table.find(buffer[3]);
	destination->write(((i3 & 0x03) << 6) + i4);
}
