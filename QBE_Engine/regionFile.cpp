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

	this->srcBufSize = pow(CHUNK_DIM, 3) * 2;
	this->dstBufSize = LZ4_compressBound(srcBufSize);
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
	if (this->eSystemEndianness == SystemEndianness::BIG)
		throw logic_error{"Trying to convert for big endianness on little endian system."};

	char* srcBuf = new char[srcBufSize];
	int dataSize = pow(CHUNK_DIM, 3);

	for (int i = 0; i < dataSize; i++) {
		char lowBit = (char)(data[i] & 0xFF);
		char highBit = (char)(data[i] >> 8);

		srcBuf[2 * i] = lowBit;
		srcBuf[(2 * i) + 1] = highBit;
	}
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
	cout << "Chunk data compressed to " << outBufSize << " bytes." << "\n";

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
