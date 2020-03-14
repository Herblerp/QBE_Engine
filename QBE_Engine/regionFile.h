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
		void readFileHeader();
		void writeFileHeader();
		~RegionFile();

		vector<char> readChunkData(Pos chunkPos);
		void writeChunkData(vector<char> chunkData);

	private:
		Pos regionPos;
		string filename;
		int regionSizeInChunks;
		int amountOfChunksInFile;
		vector<ChunkInfo> header;
	};
}



