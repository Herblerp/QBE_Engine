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

	struct ChunkInfo 
	{
		Pos chunkPos;
		int firstBytePos;
		int lastBytePos;
	};

	class RegionFile
	{
	public:
		RegionFile(Pos regionPos);
		~RegionFile();
		
		void readFileHeader();
		void writeFileHeader();
		void createFileHeader();

		vector<char> readChunkData(Pos chunkPos);
		void writeChunkData(vector<char> chunkData, Pos chunkPos);

	private:
		Pos regionPos;
		string filename;
		int headerSizeInBytes;
		int regionSizeInChunks;
		int amountOfChunksInFile;
		vector<ChunkInfo> header;

		bool compareFirstByte(int i, int j);
		int calculateChunkIndex(Pos chunkPos);
		int calculateFirstBytePos(size_t dataSize);
	};
}



