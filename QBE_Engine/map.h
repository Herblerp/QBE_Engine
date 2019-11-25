#pragma once
#include"chunk.h"

namespace NS_Data {
	class Map
	{
	public:
		Map(Pos _userPos, int _mapDim);
		~Map();
		bool UpdateUserPos(Pos _userpos);
		int blokCount;
	private:
		const int MAPDIM;

		Chunk**** mapData;
		Pos userPos;
		Chunk* LoadChunk(Pos _chunkPos);
		bool SaveChunk(Chunk* _chunk);
	};
}

