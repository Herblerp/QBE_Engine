#include "regionFile.h"
#include "lz4.h"
#include "lz4hc.h"
#include "LzmaLib.h"
#include <iostream>

using namespace std;

NS_Data::RegionFile::RegionFile(Pos regionPos)
{
	_regionPos = regionPos;

	int n = 1;
	// little endian if true
	if (*(char*)&n == 1)
	{
		_systemEndianness = SystemEndianness::LITTLE;
	}
	else
	{
		_systemEndianness = SystemEndianness::BIG;
	}

	_dataSize = (int)pow(CHUNK_DIM, 3);
}

NS_Data::RegionFile::~RegionFile()
{

}

uint16_t* NS_Data::RegionFile::ReadChunkData(Pos chunkPos)
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
	unsigned char* srcBuf;

	if (_systemEndianness == SystemEndianness::LITTLE) 
	{
		srcBuf = toByte_lEndian(data);
	}
	else 
	{
		srcBuf = toByte_bEndian(data);
	}

	unsigned char* outBuf;

	if(CHUNK_COMPRESSION_ALGORITHM == COMPRESSION_ALGORITHM::LZMA)
		outBuf = compressLZMA(srcBuf);
	if(CHUNK_COMPRESSION_ALGORITHM == COMPRESSION_ALGORITHM::LZ4)
		outBuf = compressLZ4(srcBuf);

	delete[] srcBuf;
	delete[] outBuf;
	//TODO: Save data to file
	//TODO: Edit header

	return false;
}

//Converts the given array to an array of bytes on little endian systems.
//Each short will be split into 2 bytes, the least significant byte will be put first (little endian).
unsigned char* NS_Data::RegionFile::toByte_lEndian(uint16_t* data)
{
	if (_systemEndianness == SystemEndianness::BIG)
		throw logic_error{"Trying to convert for big endianness on little endian system."};
	
	int byteCount = 0;
	bool byteMode = false;
	unsigned char* temp = new unsigned char[_dataSize*2];

	for (int i = 0; i < _dataSize; i++) 
	{
		unsigned char lowBit = data[i] & 0x00ff;
		unsigned char highBit = data[i] >> 8;
		
		if (byteMode && highBit == 0) 
		{
			temp[byteCount] = lowBit;
			byteCount++;
		}
		else if (!byteMode && highBit == 0) 
		{
			if (i < _dataSize - 3)
			{
				unsigned char highBit1 = data[i + 1] >> 8;
				unsigned char highBit2 = data[i + 2] >> 8;

				if(highBit == 0 && highBit1 == 0 && highBit2 == 0 )
				{
					temp[byteCount] = 0;
					temp[byteCount + 1] = 0;
					byteCount += 2;
					byteMode = true;

					temp[byteCount] = lowBit;
					byteCount++;
				}
				else
				{
					temp[byteCount] = lowBit;
					temp[byteCount + 1] = highBit;
					byteCount += 2;
				}
			}
			else 
			{
				temp[byteCount] = lowBit;
				temp[byteCount + 1] = highBit;
				byteCount += 2;
			}
		}
		else if (byteMode && highBit != 0) 
		{
			temp[byteCount] = 0;
			byteCount++;
			byteMode = false;
		}
		else 
		{
			temp[byteCount] = lowBit;
			temp[byteCount + 1] = highBit;
			byteCount += 2;
		}
	}
	//Set buf sizes
	SetSrcBuffSize(byteCount);
	SetDstBuffSize(byteCount + ceil(byteCount * 0.01) + 600);

	//Copy values to new array
	unsigned char* srcBuf = new unsigned char[_srcBufSize];
	memcpy(srcBuf, temp, _srcBufSize);

	//Delete temp and return srcBuf
	delete[] temp;
	return srcBuf;
}

//Converts the given array to an array of bytes on big endian systems.
//Each short will be split into 2 bytes, the least significant byte will be put first (little endian).
//TODO:Implement
unsigned char* NS_Data::RegionFile::toByte_bEndian(uint16_t* data)
{
	return nullptr;
}

unsigned char* NS_Data::RegionFile::compressLZMA(unsigned char* srcBuf) {

	unsigned char* dstBuf = new unsigned char[_dstBufSize];
	unsigned char* props = new unsigned char[LZMA_PROPS_SIZE];

	LzmaCompress(dstBuf, &_outBufSize, srcBuf, _srcBufSize, props, &_propSize, -1, 0, -1, -1, -1, -1, 2);

	cout << "Chunk compressed to " << _outBufSize << " bytes. \n";

	unsigned char* outBuf = new unsigned char[_outBufSize];
	memcpy(outBuf, dstBuf, _outBufSize);
	return outBuf;
}

unsigned char* NS_Data::RegionFile::compressLZ4(unsigned char* srcBuf)
{
	char* temp = new char[_srcBufSize];
	for(int i = 0; i<_srcBufSize; i++)
	{
		temp[i] = (char)srcBuf[i];
	}

	char* dstBuf = new char[_dstBufSize];

	_outBufSize = LZ4_compress_HC(temp, dstBuf, _srcBufSize, _dstBufSize, 4);
	cout << "Chunk data compressed to " << _outBufSize << " bytes." << "\n";

	unsigned char* outBuf = new unsigned char[_outBufSize];
	for (int i = 0; i < _outBufSize; i++)
	{
		outBuf[i] = (unsigned char)dstBuf[i];
	}
	delete[] dstBuf;
	return outBuf;
}

char* NS_Data::RegionFile::decompressData(char*)
{
	return nullptr;
}

void NS_Data::RegionFile::SetDataSize(int size)
{
	this->_dataSize = size;
}

void NS_Data::RegionFile::SetSrcBuffSize(int size)
{
	this->_srcBufSize = size;
}

void NS_Data::RegionFile::SetDstBuffSize(int size)
{
	this->_dstBufSize = size;
}

void NS_Data::RegionFile::SetOutBuffSize(int size)
{
	this->_outBufSize = size;
}