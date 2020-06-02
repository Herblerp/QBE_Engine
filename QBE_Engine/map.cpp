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
	mapData.reserve(pow(mapSizeInChunks, 3));

	int32_t minMapPos_x = cameraPos.x - (mapRadiusInChunks * chunkSizeInNodes);
	int32_t minMapPos_y = cameraPos.y - (mapRadiusInChunks * chunkSizeInNodes);
	int32_t minMapPos_z = cameraPos.z - (mapRadiusInChunks * chunkSizeInNodes);

	int32_t maxMapPos_x = cameraPos.x + (mapRadiusInChunks * chunkSizeInNodes);
	int32_t maxMapPos_y = cameraPos.y + (mapRadiusInChunks * chunkSizeInNodes);
	int32_t maxMapPos_z = cameraPos.z + (mapRadiusInChunks * chunkSizeInNodes);

	for (int z = minMapPos_z; z <= maxMapPos_z; z += chunkSizeInNodes)
	{
		for (int y = minMapPos_y; y <= maxMapPos_y; y += chunkSizeInNodes)
		{
			for (int x = minMapPos_x; x <= maxMapPos_x; x += chunkSizeInNodes)
			{
				Pos currentPos = { x,y,z };
				Pos regionPos = calculateRegionPos(currentPos);
				Pos chunkPos = calculateChunkPos(currentPos, regionPos);

				//mapData.push_back(loadChunk(regionPos, chunkPos));
			}
		}
	}
}

void Map::loadChunk(Pos regionPos, Pos chunkPos)
{

	//Region file magic here
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
}

void Map::calculateMapParameters(MapInfo mapInfo) {
	this->cameraPos = mapInfo.cameraPos;
	this->mapRadiusInChunks = mapInfo.mapDim;
	this->mapSizeInChunks = mapRadiusInChunks * 2 + 1;

	this->regionSizeInChunks = mapInfo.regionDim;
	this->chunkSizeInNodes = mapInfo.chunkDim;

	this->regionSizeInNodes = regionSizeInChunks * chunkSizeInNodes;
}
