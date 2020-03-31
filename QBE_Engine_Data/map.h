#pragma once
#include <thread>
#include "chunk.h"
//#include "regionFile.h"

namespace Data {
	class Map
	{
	public:
		Map();
		~Map();
		void loadMap(ChunkPos userPos);
		void updateMap(ChunkPos userPos);
		void saveMap();
	private:
		int mapSizeInChunks;
		int mapRadiusInChunks;
		int regionSizeInChunks;
		int regionSizeInNodes;
		int chunkSizeInNodes;
		vector<Chunk> mapData;
		//vector<RegionFile> regionFileCache;

		ChunkPos calculateRegionPos(ChunkPos playerPos);
		ChunkPos calculateChunkPos(ChunkPos playerPos, ChunkPos regionPos);

		Chunk loadChunk(ChunkPos regionPos, ChunkPos chunkPos);
	};
}

