#include "chunk.h"

Chunk::Chunk(ChunkCreateInfo info)
{
	this->chunkDim = info.chunkDim;
	this->nodeData = info.nodeData;
	this->chunkPos = info.chunkPos;
	this->regionPos = info.regionPos;
	this->regionSizeInNodes = info.regionSizeInNodes;
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

	float offset_x = static_cast<float>((regionSizeInNodes * regionPos.x) + (chunkDim * chunkPos.x));
	float offset_y = static_cast<float>((regionSizeInNodes * regionPos.y) + (chunkDim * chunkPos.y));;
	float offset_z = static_cast<float>((regionSizeInNodes * regionPos.z) + (chunkDim * chunkPos.z));;

	for (int i = 0; i < nodeData.size(); i++) {

		int z_int = i / pow(chunkDim, 2);
		int temp = i - (z_int * pow(chunkDim, 2));
		int x_int = temp % chunkDim;
		int y_int = temp / chunkDim;

		float relative_x = static_cast<float>(x_int);
		float relative_y = static_cast<float>(y_int);
		float relative_z = static_cast<float>(z_int);

		float x = static_cast<float>(x_int) + offset_x;
		float y = static_cast<float>(y_int) + offset_y;
		float z = static_cast<float>(z_int) + offset_z;

		if (nodeData[i] != 0 && (relative_x == chunkDim - 1 || !has_pos_x_neighbour_node(i))) {
			vertexData.push_back({ {1.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 1, indexCount + 2, indexCount + 2, indexCount + 3, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (relative_x == 0 || !has_neg_x_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {0.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {0.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {0.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 3, indexCount + 2, indexCount + 2, indexCount + 1, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (relative_y == chunkDim - 1 || !has_pos_y_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {0.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 3, indexCount + 2, indexCount + 2, indexCount + 1, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (relative_y == 0 || !has_neg_y_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 0.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {0.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 1, indexCount + 2, indexCount + 2, indexCount + 3, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (relative_z == chunkDim - 1 || !has_pos_z_neighbour_node(i))) {
			vertexData.push_back({ {0.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
			vertexData.push_back({ {0.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
			vertexData.push_back({ {1.0f + x, 1.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
			vertexData.push_back({ {1.0f + x, 0.0f + y, 1.0f + z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });

			uint32_t temp[] = { indexCount, indexCount + 3, indexCount + 2, indexCount + 2, indexCount + 1, indexCount };
			indexData.insert(indexData.end(), temp, temp + 6);
			indexCount += 4;
		}
		if (nodeData[i] != 0 && (relative_z == 0 || !has_neg_z_neighbour_node(i))) {
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
