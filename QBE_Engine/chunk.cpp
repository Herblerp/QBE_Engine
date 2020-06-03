#include "chunk.h"

Chunk::Chunk(ChunkCreateInfo info)
{
	this->chunkDim = info.chunkDim;
	this->nodeData = info.nodeData;
	this->dataCalculated = false;
}

void Chunk::calculateVertexData(uint32_t &indexCount)
{
	if (dataCalculated) {
		return;
	}

	indexCount = 0;

	vertexData.clear();
	indexData.clear();
	vertexData.reserve(nodeData.size());
	indexData.reserve(nodeData.size());

	for (int i = 0; i < nodeData.size(); i++) {

		int z_int = i / pow(chunkDim, 2);
		int temp = i - (z_int * pow(chunkDim, 2));
		int x_int = temp % chunkDim;
		int y_int = temp / chunkDim;


		float x = static_cast<float>(x_int);
		float y = static_cast<float>(y_int);
		float z = static_cast<float>(z_int);

		if (nodeData[i] != 0 && (x == chunkDim - 1 || !has_pos_x_neighbour_node(i))) {
			vertexData.push_back({ {1.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 1, indexCount + 2, indexCount + 2, indexCount + 3, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (x == 0 || !has_neg_x_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {0.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {0.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {0.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 3, indexCount + 2, indexCount + 2, indexCount + 1, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (y == chunkDim - 1 || !has_pos_y_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {0.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 3, indexCount + 2, indexCount + 2, indexCount + 1, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (y == 0 || !has_neg_y_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {0.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 1, indexCount + 2, indexCount + 2, indexCount + 3, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (z == chunkDim - 1 || !has_pos_z_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {0.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 3, indexCount + 2, indexCount + 2, indexCount + 1, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (z == 0 || !has_neg_z_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {0.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 1, indexCount + 2, indexCount + 2, indexCount + 3, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
	}
	dataCalculated = true;
}

std::vector<Vertex> const& Chunk::getVertexData()
{
	return vertexData;
}
std::vector<uint32_t> const& Chunk::getIndexData()
{
	return indexData;
}

bool Chunk::has_pos_x_neighbour_node(int i)
{
	if (nodeData[i + 1] == 0) {
		return false;
	}
	return true;
}
bool Chunk::has_neg_x_neighbour_node(int i)
{
	if (nodeData[i - 1] == 0) {
		return false;
	}
	return true;
}
bool Chunk::has_pos_y_neighbour_node(int i)
{
	if (nodeData[i + chunkDim] == 0) {
		return false;
	}
	return true;
}
bool Chunk::has_neg_y_neighbour_node(int i)
{
	if (nodeData[i - chunkDim] == 0) {
		return false;
	}
	return true;
}
bool Chunk::has_pos_z_neighbour_node(int i)
{
	if (nodeData[i + (chunkDim * chunkDim)] == 0) {
		return false;
	}
	return true;
}
bool Chunk::has_neg_z_neighbour_node(int i)
{
	if (nodeData[i - (chunkDim * chunkDim)] == 0) {
		return false;
	}
	return true;
}
