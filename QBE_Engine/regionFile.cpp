#include "regionFile.h"

namespace Data 
{
	RegionFile::RegionFile(Pos regionPos)
	{
		this->regionPos = regionPos;
		this->regionSizeInChunks = REGION_SIZE_IN_CHUNKS;
		this->amountOfChunksInFile = pow(regionSizeInChunks, 3);
		this->header.reserve(amountOfChunksInFile);
		this->filename = to_string(regionPos.x) + '_' + to_string(regionPos.y) + '_' + to_string(regionPos.z) + ".qbereg";

		if (filesystem::exists(this->filename)) 
		{
			readFileHeader();
		}
		else 
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
						chunkInfo.dataFirstBytePos = 0;
						chunkInfo.dataLastBytePos = 0;
						this->header.push_back(chunkInfo);
					}
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
		return vector<char>();
	}

	void RegionFile::writeChunkData(vector<char> chunkData)
	{
	}

	RegionFile::~RegionFile()
	{
		writeFileHeader();
	}
}


