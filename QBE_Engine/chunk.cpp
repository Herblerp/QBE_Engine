#include "chunk.h"
#include <stdexcept>

namespace NS_Data {

	Chunk::Chunk(uint16_t* _nodeData)
	{
		this->nodeData = _nodeData;
	}
	Chunk::~Chunk()
	{
		delete[] nodeData;
	}
	char* Chunk::compressChunk(char*)
	{
		return nullptr;
	}
	char* Chunk::decompressChunk(char*)
	{
		return nullptr;
	}
	unsigned char* Chunk::encodeRLE(uint16_t*)
	{
		return nullptr;
	}
	unsigned char* Chunk::toByte_bEndian(uint16_t*)
	{
		return nullptr;
	}
	unsigned char* Chunk::toByte_lEndian(uint16_t*)
	{
		return nullptr;
	}
	unsigned char* Chunk::compressLZMA(unsigned char* srcBuf)
	{
		return nullptr;
	}
	unsigned char* Chunk::compressLZ4(unsigned char* srcBuf)
	{
		return nullptr;
	}
}

