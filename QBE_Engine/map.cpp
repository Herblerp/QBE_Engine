#include "map.h"
#include <iostream>
#include <thread>
namespace NS_Data {

	void SaveChunk(Chunk* _chunk);

	Map::Map(Pos _userPos) : reg(Pos{ 0,0,0 })
	{
		blockCount = 0;
		chunkCount = pow(MAP_DIM, 3);
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

	void Map::SaveMap()
	{
		int threadNumber = 1;

		std::thread* t1 = nullptr;
		std::thread* t2 = nullptr;
		std::thread* t3 = nullptr;
		std::thread* t4 = nullptr;
		std::thread* t5 = nullptr;
		std::thread* t6 = nullptr;

		//TODO: Clean this up and make it scalable!
		for (auto i = 0; i < MAP_DIM; i++) {
			for (auto j = 0; j < MAP_DIM; j++) {
				for (auto k = 0; k < MAP_DIM; k++) {
					if (threadNumber == 1)
					{
						if (t1 != nullptr && t1->joinable())
						{
							t1->join();
							delete t1;
						}
						t1 = SpawnSaveThread(mapData[i][j][k]);
						threadNumber = 2;
					}
					else if (threadNumber == 2)
					{
						if (t2 != nullptr)
						{
							t2->join();
							delete t2;
						}
						t2 = SpawnSaveThread(mapData[i][j][k]);
						threadNumber = 3;
					}
					else if (threadNumber == 3)
					{
						if (t3 != nullptr)
						{
							t3->join();
							delete t3;
						}
						t3 = SpawnSaveThread(mapData[i][j][k]);
						threadNumber = 4;
					}
					else if (threadNumber == 4)
					{
						if (t4 != nullptr)
						{
							t4->join();
							delete t4;
						}
						t4 = SpawnSaveThread(mapData[i][j][k]);
						threadNumber = 5;
					}
					else if (threadNumber == 5)
					{
						if (t5 != nullptr)
						{
							t5->join();
							delete t5;
						}
						t5 = SpawnSaveThread(mapData[i][j][k]);
						threadNumber = 6;
					}
					else if (threadNumber == 6)
					{
						if (t6 != nullptr)
						{
							t6->join();
							delete t6;
						}
						t6 = SpawnSaveThread(mapData[i][j][k]);
						threadNumber = 1;
					}
				}
			}
		}

		if (t1 != nullptr && t1->joinable())
		{
			t1->join();
			delete t1;
		}
		if (t2 != nullptr && t2->joinable())
		{
			t2->join();
			delete t2;
		}
		if (t3 != nullptr && t3->joinable())
		{
			t3->join();
			delete t3;
		}
		if (t4 != nullptr && t4->joinable())
		{
			t4->join();
			delete t4;
		}
		if (t5 != nullptr && t5->joinable())
		{
			t5->join();
			delete t5;
		}
		if (t6 != nullptr && t6->joinable())
		{
			t6->join();
			delete t6;
		}


		for (auto i = 0; i < MAP_DIM; i++) {
			for (auto j = 0; j < MAP_DIM; j++)
			{
				delete[] mapData[i][j];
			}
			delete[] mapData[i];
		}
		delete[] mapData;
	}

	Map::~Map()
	{

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
			nodeData[i] = rand() % 50 + 2000;
			blockCount++;
		}

		Chunk* chunk = new Chunk(nodeData);
		return chunk;
	}

	std::thread* Map::SpawnSaveThread(Chunk* _chunk) {
		return new std::thread([=] {SaveChunk(_chunk); });
	}

	void SaveChunk(Chunk* _chunk)
	{
		RegionFile reg(Pos{ 0,0,0 });
		reg.SaveChunkData(_chunk->nodeData);
		delete _chunk;
	}
}