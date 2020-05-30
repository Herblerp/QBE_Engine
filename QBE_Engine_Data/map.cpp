//#include "map.h"
//#include <iostream>
//#include <thread>
//using namespace globals;
//
//namespace Data{
//
//	Map::Map()
//	{
//		this->mapRadiusInChunks = MAP_RADIUS_IN_CHUNKS;
//		this->mapSizeInChunks = mapRadiusInChunks * 2 + 1;
//
//		this->regionSizeInChunks = REGION_SIZE_IN_CHUNKS;
//		this->chunkSizeInNodes = CHUNK_SIZE_IN_NODES;
//		
//		this->regionSizeInNodes = regionSizeInChunks * chunkSizeInNodes;
//	}
//
//	void Map::loadMap(Pos playerPos) 
//	{
//		mapData.reserve(pow(mapSizeInChunks, 3));
//
//		Pos minMapPos;
//		minMapPos.x = playerPos.x - (mapRadiusInChunks * chunkSizeInNodes);
//		minMapPos.y = playerPos.y - (mapRadiusInChunks * chunkSizeInNodes);
//		minMapPos.z = playerPos.z - (mapRadiusInChunks * chunkSizeInNodes);
//
//		Pos maxMapPos;
//		maxMapPos.x = playerPos.x + (mapRadiusInChunks * chunkSizeInNodes);
//		maxMapPos.y = playerPos.y + (mapRadiusInChunks * chunkSizeInNodes);
//		maxMapPos.z = playerPos.z + (mapRadiusInChunks * chunkSizeInNodes);
//
//		for (int z = minMapPos.z; z <= maxMapPos.z; z += chunkSizeInNodes)
//		{
//			for (int y = minMapPos.y; y <= maxMapPos.y; y += chunkSizeInNodes)
//			{
//				for (int x = minMapPos.x; x <= maxMapPos.x; x += chunkSizeInNodes)
//				{
//					Pos currentPos = { x,y,z };
//					Pos regionPos = calculateRegionPos(currentPos);
//					Pos chunkPos = calculateChunkPos(currentPos, regionPos);
//
//					mapData.push_back(loadChunk(regionPos, chunkPos));
//				}
//			}
//		}
//	}
//
//	Chunk Map::loadChunk(ChunkPos regionPos, ChunkPos chunkPos)
//	{
//		return Chunk();
//	}
//
//	ChunkPos Map::calculateRegionPos(ChunkPos pos)
//	{
//		ChunkPos regionPos;
//		regionPos.x = pos.x / regionSizeInNodes;
//		regionPos.y = pos.y / regionSizeInNodes;
//		regionPos.z = pos.z / regionSizeInNodes;
//
//		return regionPos;
//	}
//
//	ChunkPos Map::calculateChunkPos(ChunkPos pos, ChunkPos regionPos)
//	{
//		ChunkPos chunkPos;
//		chunkPos.x = (pos.x - regionPos.x * regionSizeInNodes) / chunkSizeInNodes;
//		chunkPos.y = (pos.y - regionPos.y * regionSizeInNodes) / chunkSizeInNodes;
//		chunkPos.z = (pos.z - regionPos.z * regionSizeInNodes) / chunkSizeInNodes;
//
//		return chunkPos;
//	}
//
//	Map::~Map()
//	{
//
//	}
//
//	//void Map::SaveMap()
//	//{
//	//	int threadNumber = 1;
//
//	//	std::thread* t1 = nullptr;
//	//	std::thread* t2 = nullptr;
//	//	std::thread* t3 = nullptr;
//	//	std::thread* t4 = nullptr;
//	//	std::thread* t5 = nullptr;
//	//	std::thread* t6 = nullptr;
//
//	//	//TODO: Clean this up and make it scalable!
//	//	for (auto i = 0; i < MAP_DIM; i++) {
//	//		for (auto j = 0; j < MAP_DIM; j++) {
//	//			for (auto k = 0; k < MAP_DIM; k++) {
//	//				SaveChunk(mapData[i][j][k]);
//	//				/*if (threadNumber == 1)
//	//				{
//	//					if (t1 != nullptr && t1->joinable())
//	//					{
//	//						t1->join();
//	//						delete t1;
//	//					}
//	//					t1 = SpawnSaveThread(mapData[i][j][k]);
//	//					threadNumber = 2;
//	//				}
//	//				else if (threadNumber == 2)
//	//				{
//	//					if (t2 != nullptr)
//	//					{
//	//						t2->join();
//	//						delete t2;
//	//					}
//	//					t2 = SpawnSaveThread(mapData[i][j][k]);
//	//					threadNumber = 3;
//	//				}
//	//				else if (threadNumber == 3)
//	//				{
//	//					if (t3 != nullptr)
//	//					{
//	//						t3->join();
//	//						delete t3;
//	//					}
//	//					t3 = SpawnSaveThread(mapData[i][j][k]);
//	//					threadNumber = 4;
//	//				}
//	//				else if (threadNumber == 4)
//	//				{
//	//					if (t4 != nullptr)
//	//					{
//	//						t4->join();
//	//						delete t4;
//	//					}
//	//					t4 = SpawnSaveThread(mapData[i][j][k]);
//	//					threadNumber = 5;
//	//				}
//	//				else if (threadNumber == 5)
//	//				{
//	//					if (t5 != nullptr)
//	//					{
//	//						t5->join();
//	//						delete t5;
//	//					}
//	//					t5 = SpawnSaveThread(mapData[i][j][k]);
//	//					threadNumber = 6;
//	//				}
//	//				else if (threadNumber == 6)
//	//				{
//	//					if (t6 != nullptr)
//	//					{
//	//						t6->join();
//	//						delete t6;
//	//					}
//	//					t6 = SpawnSaveThread(mapData[i][j][k]);
//	//					threadNumber = 1;
//	//				}*/
//	//			}
//	//		}
//	//	}
//
//	//	//if (t1 != nullptr && t1->joinable())
//	//	//{
//	//	//	t1->join();
//	//	//	delete t1;
//	//	//}
//	//	//if (t2 != nullptr && t2->joinable())
//	//	//{
//	//	//	t2->join();
//	//	//	delete t2;
//	//	//}
//	//	//if (t3 != nullptr && t3->joinable())
//	//	//{
//	//	//	t3->join();
//	//	//	delete t3;
//	//	//}
//	//	//if (t4 != nullptr && t4->joinable())
//	//	//{
//	//	//	t4->join();
//	//	//	delete t4;
//	//	//}
//	//	//if (t5 != nullptr && t5->joinable())
//	//	//{
//	//	//	t5->join();
//	//	//	delete t5;
//	//	//}
//	//	//if (t6 != nullptr && t6->joinable())
//	//	//{
//	//	//	t6->join();
//	//	//	delete t6;
//	//	//}
//
//
//	//	for (auto i = 0; i < MAP_DIM; i++) {
//	//		for (auto j = 0; j < MAP_DIM; j++)
//	//		{
//	//			delete[] mapData[i][j];
//	//		}
//	//		delete[] mapData[i];
//	//	}
//	//	delete[] mapData;
//	//}
//
//	//std::thread* Map::SpawnSaveThread(Chunk* _chunk) {
//	//	return new std::thread([=] {SaveChunk(_chunk); });
//	//}
//}