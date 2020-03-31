#pragma once
#include <string>
#include <vector>
#include <bitset>

using namespace std;

namespace Data {

	class Chunk
	{
	public:
		Chunk(vector<uint16_t> nodeData);
		~Chunk();

		char* serialize();
		void deSerialize(char *);

	private:
		ChunkPos chunkPos;
		RegionPos regionPos;
		vector<uint16_t> nodeData;
	};
}

