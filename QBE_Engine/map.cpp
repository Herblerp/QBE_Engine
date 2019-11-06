#include "map.h"

Map::Map()
{
	activeChunks = new Chunk * *[renderDistance];
	for (auto i = 0; i < renderDistance; i++) {
		activeChunks[i] = new Chunk * [renderDistance];
		for (auto j = 0; j < renderDistance; j++) {
			activeChunks[i][j] = new Chunk[renderDistance];
		}
	}
}

Map::~Map()
{
	for (auto i = 0; i < renderDistance; i++) {
		for (auto j = 0; j < renderDistance; j++) {

			delete[] activeChunks[i][j];
		}
		delete[] activeChunks[i];
	}
	delete[] activeChunks;
}
