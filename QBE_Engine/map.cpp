#include "map.h"
namespace NS_Data {
	Map::Map(Pos _userPos)
	{
		blockCount = 0;

		mapData = new Chunk*** [MAP_DIM];
		for (auto i = 0; i < MAP_DIM; i++) {
			mapData[i] = new Chunk** [MAP_DIM];
			for (auto j = 0; j < MAP_DIM; j++) {
				mapData[i][j] = new Chunk*[MAP_DIM];
				for (auto k = 0; k < MAP_DIM; k++) {
					//TODO: Load appropriate position
					mapData[i][j][k] = LoadChunk(Pos{ 0,0,0 });
				}
			}
		}
	}

	Map::~Map()
	{
		for (auto i = 0; i < MAP_DIM; i++) {
			for (auto j = 0; j < MAP_DIM; j++) {
				for (auto k = 0; k < MAP_DIM; k++) {
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
		const int arrLength = pow(CHUNK_DIM, 3);

		uint16_t* nodeData = new uint16_t [arrLength];
		for (auto i = 0; i < arrLength; i++) {
			//TODO: Load appropriate node value
			nodeData[i] = 50;
			blockCount++;
		}

		Chunk* chunk = new Chunk(nodeData);
		return chunk;
	}
	bool Map::SaveChunk(Chunk* _chunk)
	{
		delete _chunk;
		return false;
	}
}