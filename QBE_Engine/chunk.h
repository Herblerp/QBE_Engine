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

		enum class SystemEndianness { LITTLE, BIG };
		SystemEndianness _systemEndianness;

		config::Pos chunkPos;
		config::Pos regionPos;

		char* compressChunk(char*);
		char* decompressChunk(char*);

		uint16_t* encodeRLE(uint16_t*,int,int&);
		unsigned char* toByte_bEndian(uint16_t*,int,int&);
		unsigned char* toByte_lEndian(uint16_t*,int,int&);
		unsigned char* compressLZMA(unsigned char*, int, size_t&);
		unsigned char* compressLZ4(unsigned char*, int, size_t&);

		//Other compression methods here

	};
}

