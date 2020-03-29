#include "regionFile.h"
#include <iterator>

namespace Data
{

	RegionFile::RegionFile(Pos regionPos, int regionSizeInChunks)
	{
		this->regionPos = regionPos;
		this->regionSizeInChunks = regionSizeInChunks;

		this->amountOfChunksInFile = pow(regionSizeInChunks, 3);
		this->headerSizeInBytes = amountOfChunksInFile * sizeof(ChunkInfo);

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

	RegionFile::~RegionFile()
	{
		writeFileHeader();
	}

	bool RegionFile::chunkHasData(Pos chunkPos) {
		ChunkInfo info = this->header.at(calculateChunkIndex(chunkPos));
		return(info.lastBytePos == 0);
	}

	vector<unsigned char> RegionFile::readChunkData(Pos chunkPos)
	{
		if (chunkPos.x >= regionSizeInChunks || chunkPos.y >= regionSizeInChunks || chunkPos.z >= regionSizeInChunks) {
			throw runtime_error("Chunk pos out of bounds.");
		}

		fstream infile;
		infile.open(filename, ios::in | ios::binary);

		ChunkInfo chunkInfo = this->header.at(calculateChunkIndex(chunkPos));
		infile.seekg(chunkInfo.firstBytePos);

		if (chunkInfo.lastBytePos - chunkInfo.firstBytePos == 0) {
			throw runtime_error("Chunk data not present in file.");
		}

		int dataSize = chunkInfo.lastBytePos - chunkInfo.firstBytePos;

		vector<unsigned char> chunkData;
		chunkData.reserve(dataSize);

		char c;
		unsigned char uc;
		for (int i = 0; i < dataSize; i++) {
			infile.read(&c, sizeof(unsigned char));
			uc = static_cast<unsigned char>(c);
			chunkData.push_back(uc);
		}

		return chunkData;
	}

	void RegionFile::writeChunkData(vector<unsigned char> chunkData, Pos chunkPos)
	{
		fstream file;

		int infoIndex = calculateChunkIndex(chunkPos);
		ChunkInfo info = this->header.at(infoIndex);

		int bestFirstBytePos = calculateFirstBytePos(chunkData.size());
		file.open(filename, fstream::binary | fstream::out | fstream::in);
		file.seekp(bestFirstBytePos);

		char c = 0;
		unsigned char uc = 0;
		for (int i = 0; i < chunkData.size(); i++) {
			uc = chunkData.at(i);
			c = static_cast<char>(uc);
			file.write((char *)&uc, sizeof(char));
		}
		file.flush();
		file.close();

		info.firstBytePos = bestFirstBytePos;
		info.lastBytePos = bestFirstBytePos + chunkData.size();

		infoIndex = calculateChunkIndex(chunkPos);
		this->header.at(infoIndex) = info;
	}

	void RegionFile::createFileHeader()
	{
		//Create header in object
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
		//Create the file
		fstream file;
		file.open(filename, fstream::binary | fstream::out);
		file.close();

		//Write the header tot he file
		writeFileHeader();
	}

	void RegionFile::readFileHeader()
	{
		fstream infile;
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
		fstream file;
		file.clear();
		file.open(filename, fstream::binary | fstream::out | fstream::in);
		file.seekp(0);

		for (int i = 0; i < header.size(); i++) {
			file.write((char*)&header.at(i), sizeof(ChunkInfo));
		}
		file.close();
	}

	bool compareFirstByte(ChunkInfo i, ChunkInfo j)
	{
		return (i.firstBytePos < j.firstBytePos);
	}

	int RegionFile::calculateFirstBytePos(size_t dataSize)
	{
		int bestFirstBytePos = 0;
		int bestSize = 0;

		int previousLastBytePos = headerSizeInBytes;

		//Sort the chunks according to their position in the file
		sort(this->header.begin(), this->header.end(), compareFirstByte);

		//Try to find a gap to fit the chunk data in
		for (int i = 0; i < this->header.size(); i++)
		{
			int size = header.at(i).firstBytePos - previousLastBytePos - 1; //Because first and last bytes are not included
			if (size >= (int)dataSize && size < bestSize)
			{
				bestFirstBytePos = previousLastBytePos + 1; //We dont want to overwrite the last byte of the previous data
				bestSize = size;
			}
			previousLastBytePos = this->header.at(i).lastBytePos;
		}

		//If no gap is found bestFirstByte will be 0
		if (bestFirstBytePos == 0 && this->header.back().lastBytePos == 0) {
			//If no chunk data is present append to header
			bestFirstBytePos = headerSizeInBytes + 1;
		}
		else {
			//If data is present append to last chunk data
			bestFirstBytePos = this->header.back().lastBytePos + 1;
		}
		return bestFirstBytePos;
	}

	int RegionFile::calculateChunkIndex(Pos chunkPos)
	{
		for (int i = 0; i < this->header.size(); i++) {
			Pos temp = this->header.at(i).chunkPos;
			if (temp.x == chunkPos.x && temp.y == chunkPos.y && temp.z == chunkPos.z) {
				return i;
			}
		}
		throw runtime_error{ "Could not find the index of the requested chunk in the header." };
	}
}


