#pragma once
#include"chunk.h"
class Map
{
private:
	const int mapDIM = 8;
	Chunk*** activeChunks;
public:
	Map();
	~Map();
};

