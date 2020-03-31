#pragma once
#include <thread>
#include "chunk.h"
#include "config.h"
#include "globals.h"
//#include "regionFile.h"

namespace Data {
	class Map
	{
	public:
		Map();
		~Map();
		void loadMap(Pos userPos);
		void updateMap(Pos userPos);
		void saveMap();
	private:
		int mapSizeInChunks;
		int mapRadiusInChunks;
		int regionSizeInChunks;
		int regionSizeInNodes;
		int chunkSizeInNodes;
		vector<Chunk> mapData;
		//vector<RegionFile> regionFileCache;

		Pos calculateRegionPos(Pos playerPos);
		Pos calculateChunkPos(Pos playerPos, Pos regionPos);

		Chunk loadChunk(Pos regionPos, Pos chunkPos);
	};
}

