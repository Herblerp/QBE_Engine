#pragma once
#include <vector>
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
		int dataFirstBytePos;
		int dataLastBytePos;
	};

	class RegionFile
	{
	public:
		RegionFile(Pos regionPos);
		void readFileHeader(string filename, int amountOfChunksInFile);
		void writeFileHeader();
		~RegionFile();

		vector<char> readChunkData(Pos chunkPos);
		void writeChunkData(vector<char> chunkData);

	private:
		Pos regionPos;
		int regionSizeInChunks;
		vector<ChunkInfo> header;
	};
}



