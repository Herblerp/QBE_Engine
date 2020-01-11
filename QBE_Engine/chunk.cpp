#include "chunk.h"
#include <stdexcept>
#include <iostream>
#include "../QBE_Engine_Compression/rlEncoder.h"
#include "../QBE_Engine_Compression/byteEncoder.h"
#include "../QBE_Engine_Compression/compression.h"

namespace NS_Data {

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
		uint16_t* rleBuf = rlEncoder::encodeRLE(nodeData, nodeDataSize, rleBufSize);

		size_t byteBufSize;
		unsigned char* byteBuf;

		if (config::ENDIANNESS == config::SYS_ENDIANNESS::LITTLE)
		{
			byteBuf = byteEncoder::toByte_lEndian(rleBuf, rleBufSize, byteBufSize);
		}
		else
		{
			byteBuf = byteEncoder::toByte_bEndian(rleBuf, rleBufSize, byteBufSize);
		}
		delete[] rleBuf;

		size_t dstBufSize;
		unsigned char* dstBuf;

		if (config::ALGORITHM == config::COMPRESSION_ALGORITHM::LZMA)
			dstBuf = compression::compressLZMA(byteBuf, byteBufSize, dstBufSize);
		if (config::ALGORITHM == config::COMPRESSION_ALGORITHM::LZ4)
			dstBuf = compression::compressLZ4(byteBuf, byteBufSize, dstBufSize);

		delete[] byteBuf;
		delete[] dstBuf;

		//TODO: Save data to file
		//TODO: Edit header

		return false;
	}
	char* Chunk::decompressChunk(char*)
	{
		return nullptr;
	}
}

