#pragma once
#include <string>
#include <vector>
#include <bitset>
#include "enums.h"

using namespace std;

namespace Data {

	struct ChunkInfo {
		ChunkPos chunkPos;
		RegionPos regionPos;
		uint8_t chunkSize;
	};

	class Chunk
	{
	public:
		Chunk(vector<uint16_t> nodeData, ChunkInfo chunkInfo);
		~Chunk();

	private:
		uint8_t chunkSize;
		ChunkPos chunkPos;
		RegionPos regionPos;
		vector<uint16_t> nodeData;
	};
}

