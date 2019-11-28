#include "regionFile.h"
#include "includes/lz4.h"

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

	this->inputBufSize = pow(CHUNK_DIM, 3) * 2;
	this->outputBufSize = LZ4_compressBound(inputBufSize);

	chunkDataInputBuffer = new char[inputBufSize];
	chunkDataOutputBuffer = new char[outputBufSize];
}

NS_Data::RegionFile::~RegionFile()
{
	delete[] chunkDataInputBuffer;
	delete[] chunkDataOutputBuffer;
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

bool NS_Data::RegionFile::SaveChunkData(uint16_t* _chunkData)
{
	//TODO: Serialize chunk data
	//TODO: Compress chunk data
	//TODO: Save data to file
	//TODO: Edit header

	return false;
}

//Converts the given array to an array of bytes on little endian systems.
//Each short will be split into 2 bytes, the least significant byte will be put first (little endian).
char* NS_Data::RegionFile::toByte_lEndian(uint16_t* chunkData)
{
	if (this->eSystemEndianness == SystemEndianness::BIG)
		throw logic_error{"Trying to convert for big endianness on little endian system."};

	for (int i = 0; i < inputBufSize; i =+ 2) {
		char lowBit = (char)(chunkData[i] & 0xFF);
		char highBit = (char)(chunkData[i] >> 8);

		this->chunkDataInputBuffer[i] = lowBit;
		this->chunkDataInputBuffer[i + 1] = highBit;
	}
	return nullptr;
}

//Converts the given array to an array of bytes on big endian systems.
//Each short will be split into 2 bytes, the least significant byte will be put first (little endian).
char* NS_Data::RegionFile::toByte_bEndian(uint16_t* chunkData)
{
	if (this->eSystemEndianness == SystemEndianness::LITTLE)
		throw logic_error{ "Trying to convert for little endianness on big endian system." };

	for (int i = 0; i < inputBufSize; i = +2) {
		char highBit = (char)(chunkData[i] & 0xFF);
		char lowBit = (char)(chunkData[i] >> 8);

		this->chunkDataInputBuffer[i] = lowBit;
		this->chunkDataInputBuffer[i + 1] = highBit;
	}

	return nullptr;
}

char* NS_Data::RegionFile::compressData(char*)
{
	return nullptr;
}

char* NS_Data::RegionFile::decompressData(char*)
{
	return nullptr;
}
