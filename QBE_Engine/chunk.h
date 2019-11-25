#pragma once
#include <string>
#include <vector>
#include "structs.h"

using namespace std;

namespace NS_Data {

	class Chunk
	{
	public:
		Chunk(uint16_t*** _nodeData);
		~Chunk();
	private:
		Pos chunkPos;
		uint16_t*** nodeData;
	};

}

