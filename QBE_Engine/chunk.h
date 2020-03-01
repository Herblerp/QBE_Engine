#pragma once
#include <string>
#include <vector>
#include "config.h"
#include <bitset>

using namespace std;

namespace Data {

	class Chunk
	{
	public:
		Chunk(uint16_t* _nodeData);
		~Chunk();
		uint16_t* nodeData;

		void SaveChunk();
		void LoadChunk();

	//private:

		enum class SystemEndianness { LITTLE, BIG };
		SystemEndianness _systemEndianness;

		config::Pos chunkPos;
		config::Pos regionPos;

		char* compressChunk();
		char* decompressChunk(char*);	
		
	};
}

