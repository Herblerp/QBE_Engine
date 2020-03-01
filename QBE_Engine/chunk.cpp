#include "chunk.h"
#include <stdexcept>
#include <iostream>
#include "../QBE_Engine_Compression/rlEncoder.h"
#include "../QBE_Engine_Compression/byteEncoder.h"
#include "../QBE_Engine_Compression/algorithms.h"

using namespace Compression;

namespace Data {

	Chunk::Chunk(uint16_t* _nodeData)
	{
		this->nodeData = _nodeData;
	}
	Chunk::~Chunk()
	{
		delete[] nodeData;
	}

	void Chunk::SaveChunk()
	{
		compressChunk();
	}

	void Chunk::LoadChunk()
	{
	}

	char* Chunk::compressChunk()
	{
		size_t nodeDataSize = pow(config::CHUNK_DIM, 3);

		size_t rleBufSize;
		uint16_t* rleBuf = RLEncoder::encodeRLE(nodeData, nodeDataSize, rleBufSize);

		std::cout << rleBufSize * 2 << "\n";

		size_t byteBufSize = 0;
		unsigned char* byteBuf;

		byteBuf = ByteEncoder::toChar(nodeData, nodeDataSize, byteBufSize);

		delete[] rleBuf;

		size_t dstBufSize = pow(config::CHUNK_DIM, 3);
		unsigned char* dstBuf = nullptr;
			
		if (config::ALGORITHM == config::COMPRESSION_ALGORITHM::LZMA)
			dstBuf = Algorithms::compressLZMA(byteBuf, byteBufSize, dstBufSize);
		if (config::ALGORITHM == config::COMPRESSION_ALGORITHM::LZ4)
			dstBuf = Algorithms::compressLZ4(byteBuf, byteBufSize, dstBufSize);

		delete[] byteBuf;
		delete[] dstBuf;

		//TODO: Save data to file
		//TODO: Edit header

		return nullptr;
	}
	char* Chunk::decompressChunk(char*)
	{
		return nullptr;
	}
}

