#include "map.h"

Map::Map(std::string mapName)
{
	this->mapName = mapName;
	this->relMapDirPath = "maps/" + mapName;
	this->relMapRegionDirPath = "maps/" + mapName + "/regions";
	this->relMapFilePath = "maps/" + mapName + "/mapData.qbemap";
}

void Map::createMap(MapInfo createInfo)
{
	std::cout << "[INFO] Creating map '" << mapName << "'...\n";

	if (!std::filesystem::exists(relMapDirPath))
	{
		try {
			MapInfo mapInfo;
			mapInfo.mapDim = createInfo.mapDim;
			mapInfo.chunkDim = createInfo.chunkDim;
			mapInfo.regionDim = createInfo.regionDim;
			mapInfo.cameraPos = createInfo.cameraPos;

			std::filesystem::create_directories(relMapRegionDirPath);

			//Create the file
			std::fstream file;
			file.open(relMapFilePath, std::fstream::binary | std::fstream::out);
			file.close();

			//Write the map data
			file.open(relMapFilePath, std::fstream::binary | std::fstream::out | std::fstream::in);
			file.seekp(0);
			file.write((char*)&mapInfo, sizeof(MapInfo));
			file.close();
			calculateMapParameters(mapInfo);
		}
		catch (std::exception e) {
			std::cout << "[ERROR] An unexpected error occured when creating the map directory: " << e.what() << "\n";
		}

		std::cout << "[INFO] Map created.\n";
	}
	else {
		std::cout << "[WARNING] Map '" << mapName << "' already exists. Aborting creation.\n";
	}
}
void Map::loadMap()
{
	std::cout << "[INFO] Loading map '" << mapName << "'...\n";

	if (std::filesystem::exists(relMapFilePath))
	{
		try {
			MapInfo temp;

			std::fstream file;
			file.open(relMapFilePath, std::ios::in | std::ios::binary);
			file.seekg(0);
			file.read((char*)&temp, sizeof(MapInfo));
			file.close();

			calculateMapParameters(temp);
		}
		catch (std::exception e) {
			std::cout << "[ERROR] An unexpected error occured while loading the map: " << e.what() << "\n";
		}
		std::cout << "[INFO] Map loaded.\n";
	}
	else {
		std::cout << "[ERROR] Map '" << mapName << "' does not exist. Aborting load.\n";
	}
}
void Map::saveMap()
{
	std::cout << "[INFO] Saving map '" << mapName << "'...\n";

	if (std::filesystem::exists(relMapFilePath))
	{
		try {
			MapInfo mapInfo;
			mapInfo.mapDim = mapSizeInChunks;
			mapInfo.chunkDim = chunkSizeInNodes;
			mapInfo.cameraPos = cameraPos;

			std::fstream file;
			file.open(relMapFilePath, std::fstream::binary | std::fstream::out | std::fstream::in);
			file.seekp(0);
			file.write((char*)&mapInfo, sizeof(MapInfo));
			file.close();
		}
		catch (std::exception e) {
			std::cout << "[ERROR] An unexpected error occured when saving the map: " << e.what() << "\n";
		}
		std::cout << "[INFO] Map saved.\n";
	}
}
void Map::deleteMap()
{
	std::cout << "[INFO] Deleting map '" << mapName << "'...\n";

	if (std::filesystem::exists(relMapDirPath))
	{
		try {
			std::filesystem::remove_all(relMapDirPath);
			std::cout << "[INFO] Map deleted.\n";
		}
		catch (std::exception e) {
			std::cout << "[ERROR]An unexpected error occured when deleting the map: " << e.what() << "\n";
		}
	}
	else {
		std::cout << "[ERROR] Map '" << mapName << "' not found. Aborting deletion.\n";
	}
}

void Map::loadMapData()
{
	std::vector<int> activeChunkIndices;

	//Load all chunks and keep track of the loaded chunks
	for (int chunk_offset_z = -mapRadiusInChunks; chunk_offset_z <= mapRadiusInChunks; chunk_offset_z += 1)
	{
		for (int chunk_offset_y = -mapRadiusInChunks; chunk_offset_y <= mapRadiusInChunks; chunk_offset_y += 1)
		{
			for (int chunk_offset_x = -mapRadiusInChunks; chunk_offset_x <= mapRadiusInChunks; chunk_offset_x += 1)
			{
				int32_t currentPos_x = cameraPos.x + (chunk_offset_x * chunkSizeInNodes);
				int32_t currentPos_y = cameraPos.y + (chunk_offset_y * chunkSizeInNodes);
				int32_t currentPos_z = cameraPos.z + (chunk_offset_z * chunkSizeInNodes);

				Pos currentPos = { currentPos_x, currentPos_y, currentPos_z };
				Pos regionPos = calculateRegionPos(currentPos);
				Pos chunkPos = calculateChunkPos(currentPos, regionPos);

				int index = 0;
				loadChunk(regionPos, chunkPos, index);
				if (index >= 0) {
					activeChunkIndices.push_back(index);
				}
			}
		}
	}
	
	vector<int> chunkIndecesToRemove;

	//Save all chunks that are not needed anymore and save their index
	for (int i = 0; i < chunks.size(); i++) {

		bool unload = true;

		for (int chunkIndex : activeChunkIndices) {
			if (i == chunkIndex) {
				unload = false;
				break;
			}
		}
		if (unload) {

			Pos chunkPos = chunks[i].getChunkPos();
			Pos chunkRegPos = chunks[i].getRegionPos();

			size_t rle_dstSize = 0;
			size_t byte_dstSize = 0;
			size_t lzma_dstSize = 0;
			size_t rle_srcSize = chunks[i].getNodeData().size();

			vector<uint16_t> vecChunkData = chunks[i].getNodeData();
			uint16_t * chunkData = &vecChunkData[0];

			uint16_t * rlencoded_data = Compression::RLEncoder::encodeRLE(chunkData, rle_srcSize, rle_dstSize);
			unsigned char* byte_data = Compression::ByteEncoder::toChar(rlencoded_data, rle_dstSize, byte_dstSize);
			delete[] rlencoded_data;
			unsigned char* lzma_data = Compression::Algorithms::compressLZ4(byte_data, byte_dstSize, lzma_dstSize);
			delete[] byte_data;
			vector<unsigned char> compressed_data(lzma_data, lzma_data + lzma_dstSize);
			delete[] lzma_data;

			Data::RegionFileCreateInfo regionCreateInfo;
			regionCreateInfo.regionDim = regionSizeInChunks;
			regionCreateInfo.filePath = "maps/" + mapName + "/regions/region" + std::to_string(chunkRegPos.x) + "." + std::to_string(chunkRegPos.y) + "." + std::to_string(chunkRegPos.z);

			Data::RegionFile reg(regionCreateInfo);

			Data::ChunkPos regChunkPos;
			
			regChunkPos.x = static_cast<uint16_t>(chunkPos.x);
			regChunkPos.y = static_cast<uint16_t>(chunkPos.y);
			regChunkPos.z = static_cast<uint16_t>(chunkPos.z);

			reg.writeChunkData(compressed_data, regChunkPos);
			chunkIndecesToRemove.push_back(i);
		}
	}
	std::sort(chunkIndecesToRemove.begin(), chunkIndecesToRemove.end(), std::greater<>());
	
	for (int index : chunkIndecesToRemove) {
		chunks.erase(chunks.begin() + index);
	}
}

void Map::loadChunk(Pos regionPos, Pos chunkPos, int& chunkIndex)
{
	for (int i = 0; i < chunks.size(); i++) {

		Pos tempRegionPos = chunks[i].getRegionPos();
		Pos tempChunkPos = chunks[i].getChunkPos();

		if (tempRegionPos.x == regionPos.x && tempRegionPos.y == regionPos.y && tempRegionPos.z == regionPos.z) {
			if (tempChunkPos.x == chunkPos.x && tempChunkPos.y == chunkPos.y && tempChunkPos.z == chunkPos.z) {
				chunkIndex = i;
				return;
			}
		}
	}

	//TODO: load chunk from region file or generate new.

	FastNoise myNoise;
	myNoise.SetNoiseType(FastNoise::SimplexFractal);

	std::vector<uint16_t> nodeData;

	nodeData = std::vector<uint16_t>(pow(chunkSizeInNodes, 3), 0);
	if (regionPos.z == -1 && chunkPos.z == 9) {
		for (int x = 0; x < chunkSizeInNodes; x++) {
			for (int y = 0; y < chunkSizeInNodes; y++) {
				int node_world_x_pos = (regionSizeInNodes * regionPos.x) + (chunkSizeInNodes * chunkPos.x) + x;
				int node_world_y_pos = (regionSizeInNodes * regionPos.y) + (chunkSizeInNodes * chunkPos.y) + y;
				int height = (myNoise.GetNoise(node_world_x_pos, node_world_y_pos) + 1) * (chunkSizeInNodes / 2);

				//Iterate over chunk column
				for (int currentHeight = 0; currentHeight < chunkSizeInNodes; currentHeight++) {
					int index = x + (y * chunkSizeInNodes) + (currentHeight * pow(chunkSizeInNodes, 2));
					if (currentHeight <= height) {
						nodeData[index] = 1;
					}
					else {
						nodeData[index] = 0;
					}
				}
			}
		}

		ChunkCreateInfo info;
		info.nodeData = nodeData;
		info.chunkDim = chunkSizeInNodes;
		info.chunkPos = chunkPos;
		info.regionSizeInNodes = regionSizeInNodes;
		info.regionPos = regionPos;

		Chunk chunk = Chunk(info);
		chunk.calculateVertexData();
		chunks.push_back(chunk);
		chunkIndex = chunks.size() - 1;
	}
	else {
		chunkIndex = -1;
	}
}

Pos Map::calculateRegionPos(Pos pos)
{
	Pos regionPos;
	regionPos.x = floor(pos.x / (float)regionSizeInNodes);
	regionPos.y = floor(pos.y / (float)regionSizeInNodes);
	regionPos.z = floor(pos.z / (float)regionSizeInNodes);

	return regionPos;
}

Pos Map::calculateChunkPos(Pos pos, Pos regionPos)
{
	Pos chunkPos;
	chunkPos.x = (pos.x - regionPos.x * regionSizeInNodes) / chunkSizeInNodes;
	chunkPos.y = (pos.y - regionPos.y * regionSizeInNodes) / chunkSizeInNodes;
	chunkPos.z = (pos.z - regionPos.z * regionSizeInNodes) / chunkSizeInNodes;

	return chunkPos;
}

bool Map::updateMapData(Pos cameraPos)
{
	//This is a temporary fix to prevent empty vertex buffers.
	//TODO:Needs to be cleaned up
	cameraPos.z = 2;

	Pos currentRegionPos = calculateRegionPos(this->cameraPos);
	Pos currentChunkPos = calculateChunkPos(this->cameraPos, currentRegionPos);

	Pos newRegionPos = calculateRegionPos(cameraPos);
	Pos newChunkPos = calculateChunkPos(cameraPos, currentRegionPos);

	if (newChunkPos.x != currentChunkPos.x || newChunkPos.y != currentChunkPos.y || newChunkPos.z != currentChunkPos.z) {
		this->cameraPos = cameraPos;
		loadMapData();
		return true;
	}
	return false;
}

std::vector<Vertex> Map::getMapVertexData()
{
	std::vector<Vertex> mapVertexData;
	for(Chunk chunk : chunks){
		std::vector<Vertex> vertexData = chunk.getVertexData();
		mapVertexData.insert(mapVertexData.end(), vertexData.begin(), vertexData.end());
	}
	return mapVertexData;
}

std::vector<uint32_t> Map::getMapIndexData()
{
	std::vector<uint32_t> mapIndexData;

	uint32_t indexCount = 0;

	for (Chunk chunk : chunks) {
		std::vector<uint32_t> indexData = chunk.getIndexData();
		for (uint32_t& index : indexData) {
			index += indexCount;
		}
		mapIndexData.insert(mapIndexData.end(), indexData.begin(), indexData.end());
		indexCount += chunk.getIndexCount();
	}
	return mapIndexData;
}

void Map::calculateMapParameters(MapInfo mapInfo) {
	this->cameraPos = mapInfo.cameraPos;
	this->mapRadiusInChunks = mapInfo.mapDim;
	this->mapSizeInChunks = mapRadiusInChunks * 2 + 1;

	this->regionSizeInChunks = mapInfo.regionDim;
	this->chunkSizeInNodes = mapInfo.chunkDim;

	this->regionSizeInNodes = regionSizeInChunks * chunkSizeInNodes;
}
