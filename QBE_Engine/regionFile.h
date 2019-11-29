#pragma once
#include <vector>
#include <stdexcept>
#include "globals.h"

namespace NS_Data {

	class RegionFile
	{
	public:
		RegionFile(Pos _regionPos);
		~RegionFile();

		uint16_t* ReadChunkData(Pos _chunkPos);
		bool SaveChunkData(uint16_t* _chunkData);

	private:

		enum class SystemEndianness{LITTLE, BIG};

		SystemEndianness eSystemEndianness;

		Pos regionPos;

		int dataSize;
		int srcBufSize;
		int dstBufSize;
		int outBufSize;
		
		char* toByte_bEndian(uint16_t*);
		char* toByte_lEndian(uint16_t*);

		char* compressData(char*);
		char* decompressData(char*);
	};

}



