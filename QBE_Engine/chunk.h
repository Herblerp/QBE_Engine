#pragma once
#include <string>
#include <vector>

using namespace std;

enum SerializeDirection{X,Z};
enum ChunkStatus { LOADING, LOADED, SAVING, SAVED };

class Chunk
{
public:
	Chunk();
	~Chunk();
private:
	const int chunkDIM = 128;
	ChunkStatus status;
	uint16_t*** nodeData;
	int x_pos;
	int y_pos;
	int z_pos;
};

