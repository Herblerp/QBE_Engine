#pragma once
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "renderer.h"
class Chunk
{
public:
	int chunkDim = 32;

	std::vector<uint16_t> nodeData;
	std::vector<Vertex> vertexData;
	std::vector<uint32_t> indexData;

	void calculateVertexData();

	bool has_pos_x_neighbour_node(int i);
	bool has_neg_x_neighbour_node(int i);
	bool has_pos_y_neighbour_node(int i);
	bool has_neg_y_neighbour_node(int i);
	bool has_pos_z_neighbour_node(int i);
	bool has_neg_z_neighbour_node(int i);
};

