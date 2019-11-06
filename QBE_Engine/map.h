#pragma once
#include"chunk.h"
class Map
{
private:
	const int renderDistance = 8;
	Chunk*** activeChunks;
public:
	Map();
	~Map();
};

