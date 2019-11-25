#include "regionFile.h"

NS_Data::RegionFile::RegionFile(Pos _regionPos)
{
	this->regionPos = _regionPos;
}

NS_Data::RegionFile::~RegionFile()
{
	//TODO: Clean up
}

uint16_t* NS_Data::RegionFile::ReadChunkData(Pos _chunkPos)
{
	//TODO: Globalize chunkDIM
	//TODO: Read file
	//TODO: Get Chunk location from header
	//TODO: Load chunk data
	//TODO: Decopress chunk data

	uint16_t* nodeData = new uint16_t [chunkDIM];
	for (auto i = 0; i < pow(chunkDIM, 3); i++) {

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
