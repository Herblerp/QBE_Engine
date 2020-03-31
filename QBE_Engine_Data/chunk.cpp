#include "chunk.h"
#include <stdexcept>
#include <iostream>
#include "../QBE_Engine_Compression/rlEncoder.h"
#include "../QBE_Engine_Compression/byteEncoder.h"
#include "../QBE_Engine_Compression/algorithms.h"

using namespace Compression;

namespace Data {

	Chunk::Chunk(vector<uint16_t> nodeData, ChunkInfo chunkInfo)
	{
		this->nodeData = nodeData;
		this->chunkPos = chunkInfo.chunkPos;
		this->regionPos = chunkInfo.regionPos;
		this->chunkSize = chunkInfo.chunkSize;
	}
	Chunk::~Chunk()
	{
	}
}

