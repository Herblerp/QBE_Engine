#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include "globals.h"
#include "globals.h"

using namespace std;
using namespace globals;

namespace Data {

	struct RegionFileInitInfo
	{

	};

	struct ChunkInfo 
	{
		Pos chunkPos;
		int firstBytePos;
		int lastBytePos;
	};

	class RegionFile
	{
	public:
		RegionFile(Pos regionPos, int regionSizeInChunks);
		~RegionFile();
		
		bool chunkHasData(Pos chunkPos);
		vector<unsigned char> readChunkData(Pos chunkPos);
		void writeChunkData(vector<unsigned char> chunkData, Pos chunkPos);

	private:
		Pos regionPos;
		string filename;
		int headerSizeInBytes;
		int regionSizeInChunks;
		int amountOfChunksInFile;
		vector<ChunkInfo> header;

		void createFileHeader();
		void readFileHeader();
		void writeFileHeader();
		//bool compareFirstByte(ChunkInfo i, ChunkInfo j);
		int calculateChunkIndex(Pos chunkPos);
		int calculateFirstBytePos(size_t dataSize);
	};
}



