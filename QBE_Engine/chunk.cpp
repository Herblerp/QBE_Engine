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

	unsigned char* Chunk::encodeRLE(uint16_t* data, int size)
	{
		uint16_t* temp = new uint16_t[size];

		for (int i = 0; i < size; i++) 
		{
			int pos = 0;
			int count = 1;

			while (data[i] == data[i + 1]) 
			{
				count++;
				i++;
			}
			if (count > 1) 
			{
				//Flag
				temp[pos] = 0;
				//Count
				temp[pos] = data[i];
				pos++;
			}
			//Value
			temp[pos] = data[i];
			pos++;
		}
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

