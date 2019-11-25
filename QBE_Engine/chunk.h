#pragma once
#include <string>
#include <vector>

using namespace std;

namespace NS_Data {

	struct ChunkPos 
	{
		int pos_x, pos_y, pos_z;
	};

	class Chunk
	{
	public:
		Chunk(uint16_t*** _nodeData);
		~Chunk();
	private:
		const int chunkDIM = 128;
		uint16_t*** nodeData;
		ChunkPos chunkPos;
	};

}

