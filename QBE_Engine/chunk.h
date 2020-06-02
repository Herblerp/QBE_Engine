#pragma once
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "renderer.h"

struct ChunkCreateInfo {
	uint8_t chunkDim;
	std::vector<uint16_t> nodeData;
};

class Chunk
{
public:

	Chunk(ChunkCreateInfo info);
	
	void calculateVertexData();

	std::vector<Vertex> const &getVertexData();
	std::vector<uint32_t> const &getIndexData();

private:
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

