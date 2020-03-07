#pragma once
#include <thread>
#include "chunk.h"
#include "config.h"
#include "globals.h"
#include "regionFile.h"

namespace Data {
	class Map
	{
	public:
		Map(int mapSize, int regionSize, int chunkSize);
		~Map();
		void loadMap(Pos userPos);
		void updateMap(Pos userPos);
		void saveMap();
	private:
		int mapRadiusInChunks;
		int regionSizeInChunks;
		int chunkSizeInNodes;
		vector<Chunk> mapData;
		vector<RegionFile> regionFileCache;

		Pos calculateRegionPos(Pos playerPos, int regionSizeInNodes);
		Pos calculateChunkPos(Pos playerPos, Pos regionPos, int regionSizeInNodes);

		Chunk loadChunk(Pos regionPos, Pos chunkPos);
	};
}

