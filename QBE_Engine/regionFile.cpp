#include "regionFile.h"

NS_Data::RegionFile::RegionFile(Pos _regionPos)
{
	this->regionPos = _regionPos;
}

NS_Data::RegionFile::~RegionFile()
{
	//TODO: Clean up
}

uint16_t*** NS_Data::RegionFile::ReadChunkData(Pos _chunkPos)
{
	//TODO: Globalize chunkDIM
	//TODO: Read file
	//TODO: Get Chunk location from header
	//TODO: Load chunk data
	//TODO: Decopress chunk data

	uint16_t*** nodeData = new uint16_t **[chunkDIM];
	for (auto i = 0; i < chunkDIM; i++) {
		nodeData[i] = new uint16_t * [chunkDIM];
		for (auto j = 0; j < chunkDIM; j++) {
			nodeData[i][j] = new uint16_t[chunkDIM];
			for (auto k = 0; k < chunkDIM; k++) {
				//TODO: Get value of node
			}
		}
	}

	return nullptr;
}

bool NS_Data::RegionFile::SaveChunkData(uint16_t*** _chunkData)
{
	//TODO: Serialize chunk data
	//TODO: Compress chunk data
	//TODO: Save data to file
	//TODO: Edit header

	return false;
}
