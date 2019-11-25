#include "map.h"

Map::Map()
{
	activeChunks = new Chunk * *[mapDIM];
	for (auto i = 0; i < mapDIM; i++) {
		activeChunks[i] = new Chunk * [mapDIM];
		for (auto j = 0; j < mapDIM; j++) {
			activeChunks[i][j] = new Chunk[mapDIM];
		}
	}
}

Map::~Map()
{
	for (auto i = 0; i < mapDIM; i++) {
		for (auto j = 0; j < mapDIM; j++) {

			delete[] activeChunks[i][j];
		}
		delete[] activeChunks[i];
	}
	delete[] activeChunks;
}
