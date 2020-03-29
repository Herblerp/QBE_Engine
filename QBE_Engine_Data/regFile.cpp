#include "regFile.h"

Data::RegFile::RegFile(RegionFileInfo initInfo)
{
	this->regionSize = initInfo.regionSize;
	this->filePath = initInfo.filePath;
	this->header.reserve(pow(regionSize, 3));

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

Data::RegFile::~RegFile()
{
	writeFileHeader();
}

vector<unsigned char> Data::RegFile::readChunkData(ChunkPos chunkPos)
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
	ChunkInfo info = this->header.at(chunkInfoIndex);

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

void Data::RegFile::writeChunkData(vector<unsigned char> chunkData, ChunkPos chunkPos)
{
	//Sort the header based on position chunk data position in the file.
	sort(this->header.begin(), this->header.end(), !compareFirstByte);

	//Get the chunkInfo
	int chunkInfoIndex = 0;
	for (int i = 0; i < this->header.size(); i++) {
		ChunkPos temp = this->header.at(i).chunkPos;
		if (temp.x == chunkPos.x && temp.y == chunkPos.y && temp.z == chunkPos.z) {
			chunkInfoIndex = i;
		}
	}
	ChunkInfo info = this->header.at(chunkInfoIndex);

	//Check if the data fits in the current gap.
	int firstBytePos = 0;
	if (info.sizeInBytes >= chunkData.size()) {
		firstBytePos = info.firstBytePos;
	}

	//If the current gap doesnt fit, try to find another gap.
	else {
		int tempGapSize = 0;
		for (int i = 1; i < this->header.size(); i++)
		{
			int gapSize = header.at(i).firstBytePos - header.at(i - 1).lastBytePos - 1;
			if (gapSize >= chunkData.size())
			{
				if (tempGapSize == 0 || (tempGapSize != 0 && gapSize < tempGapSize)) {
					tempGapSize == gapSize;
					firstBytePos == header.at(i - 1).lastBytePos + 1;
				}
			}
		}
		//If no gap is found:
		//If chunk data is present, append to last data.
		if (firstBytePos == 0 && this->header.back().lastBytePos != 0) {
			firstBytePos = this->header.back().lastBytePos + 1;
		}
		//If no chunk data is present, append to the header.
		else if (firstBytePos == 0 && this->header.back().lastBytePos == 0) {
			firstBytePos = header.size * sizeof(ChunkInfo) + 1;
		}
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

	//Save the updated chunkInfo to the header
	info.sizeInBytes = chunkData.size();
	info.firstBytePos = firstBytePos;
	info.lastBytePos = firstBytePos + chunkData.size();
	this->header.at(chunkInfoIndex) = info;
}

void Data::RegFile::createRegionFile()
{
	fstream file;
	file.open(this->filePath, fstream::binary | fstream::out);
	file.close();
}

void Data::RegFile::generateFileHeader()
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

				ChunkInfo chunkInfo;
				chunkInfo.chunkPos = chunkPos;
				chunkInfo.firstBytePos = 0;
				chunkInfo.chunkSizeInBytes = 0;
				this->header.push_back(chunkInfo);
			}
		}
	}
}

void Data::RegFile::readFileHeader()
{
	fstream file;
	file.open(this->filePath, ios::in | ios::binary);
	file.seekg(0);

	ChunkInfo info;
	for (int i = 0; i < pow(this->regionSize, 3); i++)
	{
		file.read((char*)&info, sizeof(ChunkInfo));
		this->header.push_back(info);
	}
	file.close();
}

void Data::RegFile::writeFileHeader()
{
	fstream file;
	file.open(this->filePath, fstream::binary | fstream::out | fstream::in);
	file.seekp(0);

	for (int i = 0; i < header.size(); i++) {
		file.write((char*)&header.at(i), sizeof(ChunkInfo));
	}
	file.close();
}

bool Data::RegFile::compareFirstByte(ChunkInfo i, ChunkInfo j)
{
	return (i.firstBytePos < j.firstBytePos);
}