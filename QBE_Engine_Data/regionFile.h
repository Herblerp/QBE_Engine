#pragma once
#include <string>
#include<fstream>
#include <filesystem>

using namespace std;

namespace Data {

	struct ChunkPos {
		uint16_t x;
		uint16_t y;
		uint16_t z;
	};

	struct RegionFileInfo {
		int regionSize;
		string filePath;
	};

	struct ChunkInfo {
		ChunkPos chunkPos;
		uint16_t firstBytePos;
		uint16_t lastBytePos;
		uint16_t sizeInBytes;
	};

	class RegionFile
	{
	public:
		RegionFile(RegionFileInfo info);
		~RegionFile();
	private:
		int headerSizeInBytes;
		int regionSize;				//!< The 1D size of the region. 
		string filePath;			//!< The path to the region file. 
		vector<ChunkInfo> header;	//!< Contains essential information about the chunk data stored in the file.

	public:

		/*!
			Reads the chunk data with the given position from the region file.

			@param[in] chunkPos The position of the chunk in space, relative to the region file.
			@return A vector containing the compressed chunk data.
		*/
		vector<unsigned char> readChunkData(ChunkPos chunkPos);

		/*!
			Writes the chunk with the given position to the region file.

			@param[in] chunkPos The position of the chunk in space, relative to the region file.
			@param[in] chunkData A vector containing the compressed chunk data.
		*/
		void writeChunkData(vector<unsigned char> chunkData, ChunkPos chunkPos);
	private:

		/*!
			Creates a new region file at the instance's filePath.
		*/
		void createRegionFile();

		/*!
			Generates default region header data.

			This method must only be used when creating a new regionfile. 
			Fills the instace's header with default ChunkInfo values.
		*/
		void generateFileHeader();

		/*!
			Reads the instance's header data from the regionFile at the instance's filePath.
		*/
		void readFileHeader();

		/*!
			Writes the instance's header data to the regionFile at the instance's filePath.
		*/
		void writeFileHeader();
		bool compareFirstByte(ChunkInfo i, ChunkInfo j);
	};

}

