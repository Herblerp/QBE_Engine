#pragma once
#include <vector>
#include <stdexcept>
#include "globals.h"

using namespace globals;

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
		size_t _srcBufSize;
		size_t _dstBufSize;
		size_t _outBufSize;
		size_t _propSize;
		
		unsigned char* toByte_bEndian(uint16_t*);
		unsigned char* compressLZMA(unsigned char* srcBuf);
		unsigned char* compressLZ4(unsigned char* srcBuf);
		unsigned char* toByte_lEndian(uint16_t*);

		char* compressData(char*);
		char* decompressData(char*);
	};

}



