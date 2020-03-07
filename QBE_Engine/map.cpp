#include "map.h"
#include <iostream>
#include <thread>
using namespace globals;

namespace Data{

	Map::Map(int mapRadiusInChunks, int regionSizeInChunks, int chunkSizeInNodes)
	{
		this->mapRadiusInChunks = mapRadiusInChunks;
		this->regionSizeInChunks = regionSizeInChunks;
		this->chunkSizeInNodes = chunkSizeInNodes;
	}

	void Map::loadMap(Pos playerPos) 
	{
		int mapSizeInChunks = mapRadiusInChunks * 2 + 1;
		int regionSizeInNodes = regionSizeInChunks * chunkSizeInNodes;

		mapData.reserve(pow(mapSizeInChunks, 3));

		Pos minMapPos;
		minMapPos.x = playerPos.x - (mapRadiusInChunks * chunkSizeInNodes);
		minMapPos.y = playerPos.y - (mapRadiusInChunks * chunkSizeInNodes);
		minMapPos.z = playerPos.z - (mapRadiusInChunks * chunkSizeInNodes);

		Pos maxMapPos;
		maxMapPos.x = playerPos.x + (mapRadiusInChunks * chunkSizeInNodes);
		maxMapPos.y = playerPos.y + (mapRadiusInChunks * chunkSizeInNodes);
		maxMapPos.z = playerPos.z + (mapRadiusInChunks * chunkSizeInNodes);

		for (int z = minMapPos.z; z <= maxMapPos.z; z += chunkSizeInNodes)
		{
			for (int y = minMapPos.y; y <= maxMapPos.y; y += chunkSizeInNodes)
			{
				for (int x = minMapPos.x; x <= maxMapPos.x; x += chunkSizeInNodes)
				{
					Pos currentPos = { x,y,z };
					Pos regionPos = calculateRegionPos(currentPos, regionSizeInNodes);
					Pos chunkPos = calculateChunkPos(currentPos, regionPos, regionSizeInNodes);

					mapData.push_back(loadChunk(regionPos, chunkPos));
				}
			}
		}
	}

	Chunk Map::loadChunk(Pos regionPos, Pos chunkPos) 
	{
		//Check if the region file is cashed
		//If not, load the file
		//Load the chunk from te file
		//Deserialize the chunk
	}

	Pos Map::calculateRegionPos(Pos pos, int regionSizeInNodes) 
	{
		Pos regionPos;
		regionPos.x = pos.x / regionSizeInNodes;
		regionPos.y = pos.y / regionSizeInNodes;
		regionPos.z = pos.z / regionSizeInNodes;

		return regionPos;
	}

	Pos Map::calculateChunkPos(Pos pos, Pos regionPos, int regionSizeInNodes) 
	{
		Pos chunkPos;
		chunkPos.x = (pos.x - regionPos.x * regionSizeInNodes) / chunkSizeInNodes;
		chunkPos.y = (pos.y - regionPos.y * regionSizeInNodes) / chunkSizeInNodes;
		chunkPos.z = (pos.z - regionPos.z * regionSizeInNodes) / chunkSizeInNodes;

		return chunkPos;
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
					SaveChunk(mapData[i][j][k]);
					/*if (threadNumber == 1)
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
					}*/
				}
			}
		}

		//if (t1 != nullptr && t1->joinable())
		//{
		//	t1->join();
		//	delete t1;
		//}
		//if (t2 != nullptr && t2->joinable())
		//{
		//	t2->join();
		//	delete t2;
		//}
		//if (t3 != nullptr && t3->joinable())
		//{
		//	t3->join();
		//	delete t3;
		//}
		//if (t4 != nullptr && t4->joinable())
		//{
		//	t4->join();
		//	delete t4;
		//}
		//if (t5 != nullptr && t5->joinable())
		//{
		//	t5->join();
		//	delete t5;
		//}
		//if (t6 != nullptr && t6->joinable())
		//{
		//	t6->join();
		//	delete t6;
		//}


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

	std::thread* Map::SpawnSaveThread(Chunk* _chunk) {
		return new std::thread([=] {SaveChunk(_chunk); });
	}
}