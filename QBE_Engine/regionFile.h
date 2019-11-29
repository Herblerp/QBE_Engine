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

		void SetDataSize(int size);
		void SetSrcBuffSize(int size);
		void SetDstBuffSize(int size);
		void SetOutBuffSize(int size);


	private:

		enum class SystemEndianness{LITTLE, BIG};

		SystemEndianness _systemEndianness;

		Pos _regionPos;

		int _dataSize;
		int _srcBufSize;
		int _dstBufSize;
		int _outBufSize;
		
		char* toByte_bEndian(uint16_t*);
		char* toByte_lEndian(uint16_t*);

		char* compressData(char*);
		char* decompressData(char*);
	};

}



