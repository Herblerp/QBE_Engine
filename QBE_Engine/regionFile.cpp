#include "regionFile.h"
#include "includes/lz4.h"
#include "includes/lz4hc.h"
#include <iostream>

using namespace std;

NS_Data::RegionFile::RegionFile(Pos _regionPos)
{
	this->regionPos = _regionPos;

	int n = 1;
	// little endian if true
	if (*(char*)&n == 1)
	{
		this->eSystemEndianness = SystemEndianness::LITTLE;
	}
	else
	{
		this->eSystemEndianness = SystemEndianness::BIG;
	}

	this->dataSize = pow(CHUNK_DIM, 3);
	this->srcBufSize = -1;
	this->dstBufSize = -1;
	this->outBufSize = -1;
}

NS_Data::RegionFile::~RegionFile()
{

}

uint16_t* NS_Data::RegionFile::ReadChunkData(Pos _chunkPos)
{
	//TODO: Globalize chunkDIM
	//TODO: Read file
	//TODO: Get Chunk location from header
	//TODO: Load chunk data
	//TODO: Decopress chunk data

	uint16_t* nodeData = new uint16_t [CHUNK_DIM];
	for (auto i = 0; i < pow(CHUNK_DIM, 3); i++) {

	}

	return nullptr;
}

bool NS_Data::RegionFile::SaveChunkData(uint16_t* data)
{
	char* srcBuf;

	if (eSystemEndianness == SystemEndianness::LITTLE) 
	{
		srcBuf = toByte_lEndian(data);
	}
	else 
	{
		srcBuf = toByte_bEndian(data);
	}

	char* outBuf = compressData(srcBuf);
	delete[] srcBuf;
	delete[] outBuf;
	//TODO: Save data to file
	//TODO: Edit header

	return false;
}

//Converts the given array to an array of bytes on little endian systems.
//Each short will be split into 2 bytes, the least significant byte will be put first (little endian).
char* NS_Data::RegionFile::toByte_lEndian(uint16_t* data)
{
	if (eSystemEndianness == SystemEndianness::BIG)
		throw logic_error{"Trying to convert for big endianness on little endian system."};
	
	int byteCount = 0;
	bool byteMode = false;
	char* temp = new char[dataSize*2];

	for (int i = 0; i < dataSize; i++) 
	{
		unsigned char lowBit = data[i] & 0x00ff;
		unsigned char highBit = data[i] >> 8;
		
		//Check if need to switch to 1 byte mode
		if (!byteMode && highBit == 0) {
			if (i < dataSize - 2)
			{
				unsigned char highBit1 = data[i + 1] >> 8;
				unsigned char highBit2 = data[i + 2] >> 8;

				if(highBit == 0 && highBit1 == 0 && highBit2 == 0)
				{
					temp[byteCount] = 0;
					temp[byteCount + 1] = 0;
					byteCount += 2;
					byteMode = true;
				}
			}
		}
		//Check if need to switch to 2 bytes mode
		else if (byteMode && highBit > 0) 
		{
			temp[byteCount] = 0;
			byteCount++;
			byteMode = false;
		}

		if (byteMode) 
		{
			temp[byteCount] = (char)lowBit;
			byteCount++;
		}
		else 
		{
			temp[byteCount] = (char)lowBit;
			temp[byteCount + 1] = (char)highBit;
			byteCount += 2;
		}
	}
	//Set buf sizes
	this->srcBufSize = byteCount;
	this->dstBufSize = LZ4_compressBound(byteCount);

	//Copy values to new array
	char* srcBuf = new char[byteCount];
	memcpy(srcBuf, temp, byteCount);

	//Delete temp and return srcBuf
	delete[] temp;
	return srcBuf;
}

//Converts the given array to an array of bytes on big endian systems.
//Each short will be split into 2 bytes, the least significant byte will be put first (little endian).
char* NS_Data::RegionFile::toByte_bEndian(uint16_t* data)
{
	if (this->eSystemEndianness == SystemEndianness::LITTLE)
		throw logic_error{ "Trying to convert for little endianness on big endian system." };

	char* srcBuf = new char[srcBufSize];
	int dataSize = pow(CHUNK_DIM, 3);

	for (int i = 0; i < dataSize; i++) {
		char highBit = (char)(data[i] & 0xFF);
		char lowBit = (char)(data[i] >> 8);

		srcBuf[2 * i] = lowBit;
		srcBuf[(2 * i) + 1] = highBit;
	}
	return srcBuf;
}

char* NS_Data::RegionFile::compressData(char* srcBuf)
{
	char* dstBuf = new char[dstBufSize];

	this->outBufSize = LZ4_compress_HC(srcBuf, dstBuf, srcBufSize, dstBufSize, 4);
	//cout << "Chunk data compressed to " << outBufSize << " bytes." << "\n";

	char* outBuf = new char[outBufSize];
	for (int i = 0; i < outBufSize; i++) 
	{
		outBuf[i] = dstBuf[i];
	}
	delete[] dstBuf;
	return outBuf;
}

char* NS_Data::RegionFile::decompressData(char*)
{
	return nullptr;
}
