#pragma once
#include <vector>
#include "chunk.h"

namespace NS_Data {

	struct RegionPos 
	{
		int pos_x, pos_y, pos_z;
	};

	class RegionFile
	{
	public:
		RegionFile(RegionPos _regionPos);
		~RegionFile();

		Chunk* ReadChunkData(ChunkPos _chunkPos);
		bool SaveChunkData(Chunk*)

	private:
		RegionPos regionPos;
	};

}



