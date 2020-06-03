#pragma once
#include <vector>
#include <string>
#include <filesystem>

#include "chunk.h"
#include "FastNoise.h"

struct MapInfo {
	Pos cameraPos;
	uint8_t chunkDim;
	uint8_t mapDim;
	uint8_t regionDim;
};

class Map
{
public:

	Map(std::string mapName);

	void createMap(MapInfo createInfo);
	void deleteMap();
	void loadMap();
	void saveMap();

	void loadMapData();
	bool updateMapData(Pos cameraPos);

	std::vector<Vertex> const& getMapVertexData();
	std::vector<uint32_t> const& getMapIndexData();

private:

	int32_t mapSizeInChunks;
	int32_t mapRadiusInChunks;
	int32_t regionSizeInChunks;
	int32_t regionSizeInNodes;
	int32_t chunkSizeInNodes;

	Pos cameraPos;
	Pos currentChunkPos;

	std::string mapName;
	std::string relMapDirPath;
	std::string relMapRegionDirPath;
	std::string relMapFilePath;
	
	std::vector<Chunk> mapData;
	std::vector<Vertex> mapVertexData;
	std::vector<uint32_t> mapIndexData;

	void calculateMapParameters(MapInfo maptinfo);
	Pos calculateRegionPos(Pos pos);
	Pos calculateChunkPos(Pos pos, Pos regionPos);
	void loadChunk(Pos regionPos, Pos chunkPos, uint32_t &count);
};

