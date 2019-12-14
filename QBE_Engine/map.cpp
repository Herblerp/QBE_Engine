#include "map.h"
#include <iostream>
#include <thread>
namespace NS_Data {
	Map::Map(Pos _userPos) : reg(Pos{ 0,0,0 })
	{
		blockCount = 0;
		chunkCount = 0;
		mapData = new Chunk * **[MAP_DIM];
		for (auto i = 0; i < MAP_DIM; i++) {
			mapData[i] = new Chunk * *[MAP_DIM];
			for (auto j = 0; j < MAP_DIM; j++) {
				mapData[i][j] = new Chunk * [MAP_DIM];
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

		uint16_t* nodeData = new uint16_t[arrLength];
		for (auto i = 0; i < arrLength; i++) {
			//TODO: Load appropriate node value
			nodeData[i] = rand()%50+253;
			blockCount++;
		}

		Chunk* chunk = new Chunk(nodeData);
		return chunk;
	}

	std::thread Map::SpawnSaveThread(Chunk* _chunk) {
		return std::thread([=] {SaveChunk(_chunk); });
	}

	void Map::SaveChunk(Chunk* _chunk)
	{
		reg.SaveChunkData(_chunk->nodeData);
		delete _chunk;
	}

	void kak() {
		
	}
}