#include "regionFile.h"
#include <iostream>

using namespace std;


Data::RegionFile::RegionFile(Pos regionPos)
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
}

Data::RegionFile::~RegionFile()
{

}

uint16_t* Data::RegionFile::ReadChunkData(Pos chunkPos)
{
	return nullptr;
}

bool Data::RegionFile::SaveChunkData(uint16_t* data)
{
	return false;
}
