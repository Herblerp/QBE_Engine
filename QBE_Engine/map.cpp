#include "map.h"
namespace NS_Data {
	Map::Map(Pos _userPos, int _mapDim) : MAPDIM(_mapDim) 
	{
		blockCount = 0;

		mapData = new Chunk*** [MAPDIM];
		for (auto i = 0; i < MAPDIM; i++) {
			mapData[i] = new Chunk** [MAPDIM];
			for (auto j = 0; j < MAPDIM; j++) {
				mapData[i][j] = new Chunk*[MAPDIM];
				for (auto k = 0; k < MAPDIM; k++) {
					//TODO: Load oppropriate position
					mapData[i][j][k] = LoadChunk(Pos{ 0,0,0 });
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
		const int arrLength = pow(chunkDIM, 3);

		uint16_t* nodeData = new uint16_t [arrLength];
		for (auto i = 0; i < arrLength; i++) {
			//TODO: Load appropriate node value
			nodeData[i] = uint16_t(5000);
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