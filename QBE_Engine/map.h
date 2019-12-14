#pragma once
#include <thread>
#include "chunk.h"
#include "globals.h"
#include "regionFile.h"

namespace NS_Data {
	class Map
	{
	public:
		Map(Pos _userPos);
		void SaveMap();
		~Map();
		bool UpdateUserPos(Pos _userpos);
		int blockCount;
		int chunkCount;
	private:
		RegionFile reg;
		Chunk**** mapData;
		Pos userPos;
		Chunk* LoadChunk(Pos _chunkPos);
		std::thread* SpawnSaveThread(Chunk* _chunk);
	};
}

