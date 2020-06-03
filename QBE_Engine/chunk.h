#pragma once
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "renderer.h"

struct Pos {
	int32_t x;
	int32_t y;
	int32_t z;
};

struct ChunkCreateInfo {
	uint8_t chunkDim;				
	std::vector<uint16_t> nodeData;
};

class Chunk
{
public:

	Chunk(ChunkCreateInfo info);
	
	void calculateVertexData(uint32_t &indexCount);

	std::vector<Vertex> const &getVertexData();
	std::vector<uint32_t> const &getIndexData();

private:
	bool dataCalculated;

	uint8_t chunkDim;
	std::vector<uint16_t> nodeData;
	std::vector<Vertex> vertexData;
	std::vector<uint32_t> indexData;

	bool has_pos_x_neighbour_node(int i);
	bool has_neg_x_neighbour_node(int i);
	bool has_pos_y_neighbour_node(int i);
	bool has_neg_y_neighbour_node(int i);
	bool has_pos_z_neighbour_node(int i);
	bool has_neg_z_neighbour_node(int i);
};

