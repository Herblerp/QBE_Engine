#include "regionFile.h"
#include <iostream>

using namespace std;

namespace Data 
{
	RegionFile::RegionFile(Pos regionPos, int regionSizeInChunks)
	{
		this->regionPos = regionPos;
		this->regionSizeInChunks = regionSizeInChunks;

		header.reserve(pow(regionSizeInChunks, 3));
	}

	RegionFile::~RegionFile()
	{

	}

	vector<char> RegionFile::readChunkData(Pos chunkPos)
	{
		return vector<char>();
	}

	void RegionFile::writeChunkData(vector<char> chunkData)
	{
	}
}


