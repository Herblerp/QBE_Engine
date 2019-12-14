#pragma once
#include <string>
#include <vector>
#include "globals.h"

using namespace std;

namespace NS_Data {

	class Chunk
	{
	public:
		Chunk(uint16_t* _nodeData);
		~Chunk();
		uint16_t* nodeData;
	private:
		globals::Pos chunkPos;
	};

}

