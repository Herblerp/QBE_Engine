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
	mapVertexData.clear();
	mapIndexData.clear();

	uint32_t totalIndexCount = 0;
	//mapData.reserve(pow(mapSizeInChunks, 3));

	for (int chunk_offset_z = -mapRadiusInChunks; chunk_offset_z <= mapRadiusInChunks; chunk_offset_z += 1)
	{
		for (int chunk_offset_y = -mapRadiusInChunks; chunk_offset_y <= mapRadiusInChunks; chunk_offset_y += 1)
		{
			for (int chunk_offset_x = -mapRadiusInChunks; chunk_offset_x <= mapRadiusInChunks; chunk_offset_x += 1)
			{
				int32_t currentPos_x = cameraPos.x + (chunk_offset_x * chunkSizeInNodes);
				int32_t currentPos_y = cameraPos.y + (chunk_offset_y * chunkSizeInNodes);
				int32_t currentPos_z = cameraPos.z + (chunk_offset_z * chunkSizeInNodes);

				Pos currentPos = { currentPos_x, currentPos_y, currentPos_z};
				Pos regionPos = calculateRegionPos(currentPos);
				Pos chunkPos = calculateChunkPos(currentPos, regionPos);
				loadChunk(regionPos, chunkPos, totalIndexCount);
			}
		}
	}
}

void Map::loadChunk(Pos regionPos, Pos chunkPos, uint32_t &indexCount)
{
	//Perlin noise algorithm and region file loading here 
	std::vector<uint16_t> nodeData;
	if (regionPos.z >= 0) {
		nodeData = std::vector<uint16_t>(pow(chunkSizeInNodes, 3), 0);
	}
	else {
		nodeData = std::vector<uint16_t>(pow(chunkSizeInNodes, 3), 1);
	}
	//end of perlin noise algorithm

	ChunkCreateInfo info;
	info.nodeData = nodeData;
	info.chunkDim = chunkSizeInNodes;

	Chunk chunk = Chunk(info);
	uint32_t chunkIndexCount = 0;
	chunk.calculateVertexData(chunkIndexCount);

	float offset_x = static_cast<float>((regionSizeInNodes * regionPos.x) + (chunkSizeInNodes * chunkPos.x));
	float offset_y = static_cast<float>((regionSizeInNodes * regionPos.y) + (chunkSizeInNodes * chunkPos.y));;
	float offset_z = static_cast<float>((regionSizeInNodes * regionPos.z) + (chunkSizeInNodes * chunkPos.z));;

	glm::vec3 offset(offset_x,offset_y,offset_z);

	std::vector<Vertex> vertexData = chunk.getVertexData();
	for (Vertex &vertex : vertexData) {
		vertex.pos += offset;
	}

	std::vector<uint32_t> indexData = chunk.getIndexData();
	for (uint32_t &index : indexData) {
		index += indexCount;
	}

	mapVertexData.insert(mapVertexData.end(), vertexData.begin(), vertexData.end());
	mapIndexData.insert(mapIndexData.end(), indexData.begin(), indexData.end());
	indexCount += chunkIndexCount;
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

void Map::updateMapData(Pos cameraPos)
{
	Pos currentRegionPos = calculateRegionPos(this->cameraPos);
	Pos currentChunkPos = calculateChunkPos(this->cameraPos, currentRegionPos);

	Pos newRegionPos = calculateRegionPos(cameraPos);
	Pos newChunkPos = calculateChunkPos(cameraPos, currentRegionPos);

	if (newChunkPos.x != currentChunkPos.x || newChunkPos.y != currentChunkPos.y || newChunkPos.z != currentChunkPos.z) {
		this->cameraPos = cameraPos;
		loadMapData();
	}
}

std::vector<Vertex> const& Map::getMapVertexData()
{
	return mapVertexData;
}

std::vector<uint32_t> const& Map::getMapIndexData()
{
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
