#include "regionFile.h"
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
}

NS_Data::RegionFile::~RegionFile()
{

}

uint16_t* NS_Data::RegionFile::ReadChunkData(Pos chunkPos)
{
	return nullptr;
}

bool NS_Data::RegionFile::SaveChunkData(uint16_t* data)
{
	return false;
}
