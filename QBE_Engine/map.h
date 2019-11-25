#pragma once
#include"chunk.h"

namespace NS_Data {

	struct UserPos
	{
		int pos_x, pos_y, pos_z;
	};


	class Map
	{
	public:
		Map(UserPos _userPos, int _mapDIM);
		~Map();
		bool UpdateUserPos(UserPos _userpos);
	private:
		const int mapDIM;
		Chunk**** mapData;
		UserPos userPos;
		Chunk* LoadChunk(ChunkPos _chunkPos);
		bool SaveChunk(Chunk* _chunk);
	};
}

