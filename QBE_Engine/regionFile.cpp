#include "regionFile.h"

namespace Data 
{
	RegionFile::RegionFile(Pos regionPos)
	{
		this->regionPos = regionPos;
		this->regionSizeInChunks = REGION_SIZE_IN_CHUNKS;
		this->headerSizeInBytes = REGION_SIZE_IN_CHUNKS * sizeof(ChunkInfo);
		this->amountOfChunksInFile = pow(regionSizeInChunks, 3);
		this->header.reserve(amountOfChunksInFile);
		this->filename = to_string(regionPos.x) + '_' + to_string(regionPos.y) + '_' + to_string(regionPos.z) + ".qbereg";

		if (filesystem::exists(this->filename)) 
		{
			readFileHeader();
		}
		else 
		{
			createFileHeader();
		}
	}

	void RegionFile::createFileHeader() 
	{
		for (int chunkPosZ = 0; chunkPosZ < this->regionSizeInChunks; chunkPosZ++)
		{
			for (int chunkPosY = 0; chunkPosY < this->regionSizeInChunks; chunkPosY++)
			{
				for (int chunkPosX = 0; chunkPosX < this->regionSizeInChunks; chunkPosX++)
				{
					Pos chunkPos;
					chunkPos.x = chunkPosX;
					chunkPos.y = chunkPosY;
					chunkPos.z = chunkPosZ;

					ChunkInfo chunkInfo;
					chunkInfo.chunkPos = chunkPos;
					chunkInfo.firstBytePos = 0;
					chunkInfo.lastBytePos = 0;
					this->header.push_back(chunkInfo);
				}
			}
		}
	}

	void RegionFile::readFileHeader() 
	{
		ifstream infile;
		infile.open(this->filename, ios::in | ios::binary);
		infile.seekg(0);

		ChunkInfo info;
		for (int chunkCount = 0; chunkCount < this->amountOfChunksInFile; chunkCount++)
		{
			infile.read((char*)&info, sizeof(ChunkInfo));
			this->header.push_back(info);
		}
		infile.close();
	}

	void RegionFile::writeFileHeader()
	{
		ofstream outfile;
		outfile.open(this->filename, ios::out | ios::binary);

		for (int i = 0; i < header.size(); i++) {
			outfile.write((char*)&header.at(i), sizeof(ChunkInfo));
		}
		outfile.close();
	}

	vector<char> RegionFile::readChunkData(Pos chunkPos)
	{
		ifstream infile;
		infile.open(filename, ios::in | ios::binary);
		infile.seekg(0);

		return vector<char>();
	}

	void RegionFile::writeChunkData(vector<char> chunkData, Pos chunkPos)
	{
		fstream file;

		ChunkInfo info = this->header.at(calculateChunkIndex(chunkPos));

		int bestFirstBytePos = calculateFirstBytePos(chunkData.size());
		file.open(filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
		file.seekg(bestFirstBytePos);
		file.write((char*)&chunkData, chunkData.size());
		file.close();
	}

	int RegionFile::calculateFirstBytePos(size_t dataSize) 
	{
		int bestFirstBytePos = 0;
		int bestSize = 0;

		int previousLastBytePos = headerSizeInBytes;

		sort(this->header.begin(), this->header.end(), compareFirstByte);
		for (int i = 0; i < this->header.size(); i++) 
		{
			int size = header.at(i).firstBytePos - previousLastBytePos - 1; //Because the bytes are included
			if (size > dataSize && size < bestSize) 
			{
				bestFirstBytePos = previousLastBytePos + 1; //We dont want to overwrite the last byte of the previous data
				bestSize = size;
			}
			previousLastBytePos = this->header.at(i).lastBytePos;
		}
		return bestFirstBytePos;
	}

	bool RegionFile::compareFirstByte(int i, int j) 
	{
		return (i < j);
	}

	int RegionFile::calculateChunkIndex(Pos chunkPos) 
	{
		return chunkPos.x + chunkPos.y * pow(CHUNK_SIZE_IN_NODES, 2) + chunkPos.z * pow(CHUNK_SIZE_IN_NODES, 3);
	}

	RegionFile::~RegionFile()
	{
		writeFileHeader();
	}
}


