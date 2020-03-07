#pragma once
#include <vector>
#include <stdexcept>
#include "globals.h"

using namespace globals;

namespace Data {

	struct ChunkInfo 
	{
		Pos chunkPos;
		int dataFirstBytePos;
		int dataLastBytePos;
	};

	class RegionFile
	{
	public:
		RegionFile(Pos regionPos, int regionSizeInChunks);
		~RegionFile();

		vector<char> readChunkData(Pos chunkPos);
		void writeChunkData(vector<char> chunkData);

	private:
		Pos regionPos;
		int regionSizeInChunks;
		vector<ChunkInfo> header;
	};
}



