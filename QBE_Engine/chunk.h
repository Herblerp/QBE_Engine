#pragma once
#include <string>

using namespace std;

class Chunk
{
public:
	Chunk();
	~Chunk();
	bool loadChunck();
	bool saveChunck();
	enum ChunkStatus {LOADING};
private:
	const int DIM = 128;
	ChunkStatus status;
	uint16_t*** nodeData;
	int x_pos;
	int y_pos;
	int z_pos;
	
};

