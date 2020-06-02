#include "regionFile.h"

namespace Data {

	RegionFile::RegionFile(RegionFileCreateInfo info)
	{
		this->regionSize = info.regionDim;
		this->filePath = info.filePath;
		this->header.reserve(pow(regionSize, 3));
		this->headerSizeInBytes = pow(regionSize, 3) * sizeof(ChunkHeaderInfo);

		if (filesystem::exists(this->filePath))
		{
			readFileHeader();
		}
		else
		{
			createRegionFile();
			generateFileHeader();
			writeFileHeader();
		}
	}

	RegionFile::~RegionFile()
	{
		writeFileHeader();
	}

	vector<unsigned char> Data::RegionFile::readChunkData(ChunkPos chunkPos)
	{
		fstream file;
		file.open(this->filePath, ios::in | ios::binary);

		//Get the chunkInfo
		int chunkInfoIndex = 0;
		for (int i = 0; i < this->header.size(); i++) {
			ChunkPos temp = this->header.at(i).chunkPos;
			if (temp.x == chunkPos.x && temp.y == chunkPos.y && temp.z == chunkPos.z) {
				chunkInfoIndex = i;
			}
		}
		ChunkHeaderInfo info = this->header.at(chunkInfoIndex);

		file.seekg(info.firstBytePos);

		vector<unsigned char> chunkData;
		chunkData.reserve(info.sizeInBytes);

		char c;
		unsigned char uc;
		for (int i = 0; i < info.sizeInBytes; i++) {
			file.read(&c, sizeof(unsigned char));
			uc = static_cast<unsigned char>(c);
			chunkData.push_back(uc);
		}

		return chunkData;
	}

	bool compareFirstByte(ChunkHeaderInfo i, ChunkHeaderInfo j)
	{
		return (i.firstBytePos < j.firstBytePos);
	}

	void RegionFile::writeChunkData(vector<unsigned char> chunkData, ChunkPos chunkPos)
	{
		//Get the chunkInfo
		int chunkInfoIndex = 0;
		for (int i = 0; i < this->header.size(); i++) {
			ChunkPos temp = this->header.at(i).chunkPos;
			if (temp.x == chunkPos.x && temp.y == chunkPos.y && temp.z == chunkPos.z) {
				chunkInfoIndex = i;
			}
		}
		ChunkHeaderInfo info = this->header.at(chunkInfoIndex);
		info.firstBytePos = this->headerSizeInBytes;
		info.lastBytePos = this->headerSizeInBytes;
		info.sizeInBytes = 0;
		this->header.at(chunkInfoIndex) = info;

		//Sort the header based on position chunk data position in the file.
		sort(this->header.begin(), this->header.end(), Data::compareFirstByte);

		//Try to find a gap that fits the data
		int firstBytePos = 0;
		int tempGapSize = 0;
		for (int i = 1; i < this->header.size(); i++)
		{
			int gapSize = header.at(i).firstBytePos - header.at(i - 1).lastBytePos - 1;
			if (gapSize >= (int)chunkData.size())
			{
				if (tempGapSize == 0 || (tempGapSize != 0 && gapSize < tempGapSize)) {
					tempGapSize = gapSize;
					firstBytePos = header.at(i - 1).lastBytePos + 1;
				}
			}
		}
		//When no gap is found:
		//If chunk data is present, append to last data.

		if (firstBytePos == 0 && this->header.back().lastBytePos != this->headerSizeInBytes) {
			firstBytePos = this->header.back().lastBytePos + 1;
		}
		//If no chunk data is present, append to the header.
		else if (firstBytePos == 0 && this->header.back().lastBytePos == this->headerSizeInBytes) {
			firstBytePos = this->header.size() * sizeof(ChunkHeaderInfo) + 1;
		}

		//Write the data to the file
		fstream file;
		file.open(this->filePath, fstream::binary | fstream::out | fstream::in);
		file.seekp(firstBytePos);

		char c = 0;
		unsigned char uc = 0;
		for (int i = 0; i < chunkData.size(); i++) {
			uc = chunkData.at(i);
			c = static_cast<char>(uc);
			file.write((char*)&uc, sizeof(char));
		}
		file.close();

		//Search for the info index.
		for (int i = 0; i < this->header.size(); i++) {
			ChunkPos temp = this->header.at(i).chunkPos;
			if (temp.x == chunkPos.x && temp.y == chunkPos.y && temp.z == chunkPos.z) {
				chunkInfoIndex = i;
			}
		}

		//Save the updated chunkInfo to the header
		info.sizeInBytes = chunkData.size();
		info.firstBytePos = firstBytePos;
		info.lastBytePos = firstBytePos + chunkData.size();
		this->header.at(chunkInfoIndex) = info;
	}

	void RegionFile::createRegionFile()
	{
		fstream file;
		file.open(this->filePath, fstream::binary | fstream::out);
		file.close();
	}

	void RegionFile::generateFileHeader()
	{
		for (uint16_t y = 0; y < this->regionSize; y++)
		{
			for (uint16_t z = 0; z < this->regionSize; z++)
			{
				for (uint16_t x = 0; x < this->regionSize; x++)
				{
					ChunkPos chunkPos;
					chunkPos.x = x;
					chunkPos.y = y;
					chunkPos.z = z;

					ChunkHeaderInfo chunkInfo;
					chunkInfo.chunkPos = chunkPos;
					chunkInfo.firstBytePos = this->headerSizeInBytes;
					chunkInfo.lastBytePos = this->headerSizeInBytes;
					chunkInfo.sizeInBytes = 0;
					this->header.push_back(chunkInfo);
				}
			}
		}
	}

	void RegionFile::readFileHeader()
	{
		fstream file;
		file.open(this->filePath, ios::in | ios::binary);
		file.seekg(0);

		ChunkHeaderInfo info;
		for (int i = 0; i < pow(this->regionSize, 3); i++)
		{
			file.read((char*)&info, sizeof(ChunkHeaderInfo));
			this->header.push_back(info);
		}
		file.close();
	}

	void RegionFile::writeFileHeader()
	{
		fstream file;
		file.open(this->filePath, fstream::binary | fstream::out | fstream::in);
		file.seekp(0);

		for (int i = 0; i < header.size(); i++) {
			file.write((char*)&header.at(i), sizeof(ChunkHeaderInfo));
		}
		file.close();
	}

}