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
	Pos chunkPos;
	Pos regionPos;
	int32_t chunkDim;
	int32_t regionSizeInNodes;
	std::vector<uint16_t> nodeData;
};

class Chunk
{
public:

	Chunk(ChunkCreateInfo info);
	
	void calculateVertexData();

	Pos getChunkPos();
	Pos getRegionPos();

	std::uint32_t getIndexCount();
	std::vector<uint16_t> &getNodeData();
	std::vector<Vertex> const &getVertexData();
	std::vector<uint32_t> const &getIndexData();

private:
	bool dataCalculated;

	Pos chunkPos;
	Pos regionPos;
	int32_t chunkDim;
	int32_t regionSizeInNodes;
	uint32_t indexCount;

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

