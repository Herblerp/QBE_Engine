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

		int inputBufSize;
		int outputBufSize;

		char* chunkDataInputBuffer;
		char* chunkDataOutputBuffer;

		char* toByte_lEndian(uint16_t*);
		char* toByte_bEndian(uint16_t*);

		char* compressData(char*);
		char* decompressData(char*);
	};

}



