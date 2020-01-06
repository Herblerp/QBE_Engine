#pragma once
#include <string>
#include <vector>
#include "config.h"

using namespace std;

namespace NS_Data {

	class Chunk
	{
	public:
		Chunk(uint16_t* _nodeData);
		~Chunk();
		uint16_t* nodeData;

		void SaveChunk();
		void LoadChunk();

	private:

		enum class RleDirection { XYZ, YXZ };
		enum class SystemEndianness { LITTLE, BIG };
		SystemEndianness _systemEndianness;

		config::Pos chunkPos;
		config::Pos regionPos;

		size_t _srcBufSize;
		size_t _dstBufSize;
		size_t _outBufSize;
		size_t _propSize;

		char* compressChunk(char*);
		char* decompressChunk(char*);

		unsigned char* encodeRLE(uint16_t*,int);
		unsigned char* toByte_bEndian(uint16_t*);
		unsigned char* toByte_lEndian(uint16_t*);
		unsigned char* compressLZMA(unsigned char* srcBuf);
		unsigned char* compressLZ4(unsigned char* srcBuf);

		//Other compression methods here

	};
}

