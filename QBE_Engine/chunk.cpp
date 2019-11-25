#include "chunk.h"
#include <stdexcept>

Chunk::Chunk()
{
	status = LOADING;

	nodeData = new uint16_t * *[chunkDIM];
	for (auto i = 0; i < chunkDIM; i++) {
		nodeData[i] = new uint16_t * [chunkDIM];
		for (auto j = 0; j < chunkDIM; j++) {
			nodeData[i][j] = new uint16_t[chunkDIM];
		}
	}
}

Chunk::~Chunk()
{
	for (auto i = 0; i < chunkDIM; i++) {
		for (auto j = 0; j < chunkDIM; j++) {
			delete[] nodeData[i][j];
		}
		delete[] nodeData[i];
	}
	delete[] nodeData;
}



