#pragma once
#include <string>
#include <vector>
#include "config.h"
#include <bitset>

using namespace std;

namespace NS_Data {

	class Chunk
	{
		#ifdef UNIT_TEST
			friend CompressionTests;
		#endif

	public:
		Chunk(uint16_t* _nodeData);
		~Chunk();
		uint16_t* nodeData;

		void SaveChunk();
		void LoadChunk();

	//private:

		enum class SystemEndianness { LITTLE, BIG };
		SystemEndianness _systemEndianness;

		config::Pos chunkPos;
		config::Pos regionPos;

		char* compressChunk();
		char* decompressChunk(char*);

		uint16_t* decodeRLE(uint16_t*, size_t, size_t&);
		uint16_t* encodeRLE(uint16_t*, size_t, size_t&);
		unsigned char* toByte_bEndian(uint16_t*, size_t, size_t&);
		unsigned char* toByte_lEndian(uint16_t*, size_t, size_t&);
		unsigned char* compressLZMA(unsigned char*, size_t, size_t&);
		unsigned char* compressLZ4(unsigned char*, size_t, size_t&);

		//Other compression methods here

	};
}

