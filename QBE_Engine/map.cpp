#include "map.h"
namespace NS_Data {
	Map::Map(Pos _userPos, int _mapDim) : MAPDIM(_mapDim) 
	{
		blokCount = 0;

		mapData = new Chunk*** [MAPDIM];
		for (auto i = 0; i < MAPDIM; i++) {
			mapData[i] = new Chunk** [MAPDIM];
			for (auto j = 0; j < MAPDIM; j++) {
				mapData[i][j] = new Chunk*[MAPDIM];
				for (auto k = 0; k < MAPDIM; k++) {
					mapData[i][j][k] = LoadChunk(Pos{});
				}
			}
		}
	}

	Map::~Map()
	{
		for (auto i = 0; i < MAPDIM; i++) {
			for (auto j = 0; j < MAPDIM; j++) {
				for (auto k = 0; k < MAPDIM; k++) {
					SaveChunk(mapData[i][j][k]);
				}
				delete[] mapData[i][j];
			}
			delete[] mapData[i];
		}
		delete[] mapData;
	}

	bool Map::UpdateUserPos(Pos _userpos)
	{
		return false;
	}
	Chunk* Map::LoadChunk(Pos _chunkPos)
	{
		const int chunkDIM = 32;

		uint16_t*** nodeData = new uint16_t * *[chunkDIM];
		for (auto i = 0; i < chunkDIM; i++) {
			nodeData[i] = new uint16_t * [chunkDIM];
			for (auto j = 0; j < chunkDIM; j++) {
				nodeData[i][j] = new uint16_t[chunkDIM];
				for (auto k = 0; k < chunkDIM; k++) {
					nodeData[i][j][k] = 5;
					blokCount++;
				}
			}
		}

		Chunk* chunk = new Chunk(nodeData);
		return chunk;
	}
	bool Map::SaveChunk(Chunk* _chunk)
	{
		//Destroy chunks here!
		return false;
	}
}