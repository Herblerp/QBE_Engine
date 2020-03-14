#include "regionFile.h"

namespace Data 
{
	RegionFile::RegionFile(Pos regionPos)
	{
		this->regionPos = regionPos;
		this->regionSizeInChunks = REGION_SIZE_IN_CHUNKS;

		int amountOfChunksInFile = pow(regionSizeInChunks, 3);
		this->header.reserve(amountOfChunksInFile);

		string filename = to_string(regionPos.x) + '_' + to_string(regionPos.y) + '_' + to_string(regionPos.z) + ".qbereg";

		if (filesystem::exists(filename)) 
		{

		}
		else 
		{
			for (int chunkPosZ = 0; chunkPosZ < regionSizeInChunks; chunkPosZ++)
			{
				for (int chunkPosY = 0; chunkPosY < regionSizeInChunks; chunkPosY++)
				{
					for (int chunkPosX = 0; chunkPosX < regionSizeInChunks; chunkPosX++) 
					{
						Pos chunkPos;
						chunkPos.x = chunkPosX;
						chunkPos.y = chunkPosY;
						chunkPos.z = chunkPosZ;

						ChunkInfo chunkInfo;
						chunkInfo.chunkPos = chunkPos;
						chunkInfo.dataFirstBytePos = 0;
						chunkInfo.dataLastBytePos = 0;
						this->header.push_back(chunkInfo);
					}
				}
			}
		}
	}

	void RegionFile::readFileHeader(string filename, int amountOfChunksInFile) 
	{
		fstream infile;
		infile.open(filename, ios::in | ios::binary);
		infile.seekg(0);

		ChunkInfo info;
		for (int chunkCount = 0; chunkCount < amountOfChunksInFile; chunkCount++)
		{
			infile.read((char*)&info, sizeof(ChunkInfo));
			this->header.push_back(info);
		}
	}

	void RegionFile::writeFileHeader() {

	}

	vector<char> RegionFile::readChunkData(Pos chunkPos)
	{
		return vector<char>();
	}

	void RegionFile::writeChunkData(vector<char> chunkData)
	{
	}

	RegionFile::~RegionFile()
	{

	}
}


