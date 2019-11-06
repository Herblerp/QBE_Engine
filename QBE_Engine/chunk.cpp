#include "chunk.h"

Chunk::Chunk()
{
	status = LOADING;

	nodeData = new uint16_t * *[DIM];
	for (auto i = 0; i < DIM; i++) {
		nodeData[i] = new uint16_t * [DIM];
		for (auto j = 0; j < DIM; j++) {
			nodeData[i][j] = new uint16_t[DIM];
		}
	}
}

Chunk::~Chunk()
{
	for (auto i = 0; i < DIM; i++) {
		for (auto j = 0; j < DIM; j++) {
			delete[] nodeData[i][j];
		}
		delete[] nodeData[i];
	}
	delete[] nodeData;
}

bool Chunk::loadChunck()
{
	return false;
}

bool Chunk::saveChunck()
{
	return false;
}


