#include "chunk.h"
#include <stdexcept>
#include <LzmaLib.h>
#include <iostream>
#include <lz4hc.h>

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
		uint16_t* rleBuf = encodeRLE(nodeData, nodeDataSize, rleBufSize);

		size_t byteBufSize;
		unsigned char* byteBuf;

		if (config::ENDIANNESS == config::SYS_ENDIANNESS::LITTLE)
		{
			byteBuf = toByte_lEndian(rleBuf, rleBufSize, byteBufSize);
		}
		else
		{
			byteBuf = toByte_bEndian(rleBuf, rleBufSize, byteBufSize);
		}
		delete[] rleBuf;

		size_t dstBufSize;
		unsigned char* dstBuf;

		if (config::ALGORITHM == config::COMPRESSION_ALGORITHM::LZMA)
			dstBuf = compressLZMA(byteBuf, byteBufSize, dstBufSize);
		if (config::ALGORITHM == config::COMPRESSION_ALGORITHM::LZ4)
			dstBuf = compressLZ4(byteBuf, byteBufSize, dstBufSize);

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

	#pragma region Compression_algorithms

	uint16_t* Chunk::decodeRLE(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
	{
		const int tmpSize = pow(config::CHUNK_DIM, 3);

		uint16_t* tmpBuf = new uint16_t[tmpSize];
		int pos = 0;

		for (int i = 0; i < srcSize; i++)
		{
			if (srcBuf[i] == 0) 
			{
				int count = srcBuf[i + 1];
				uint16_t value = srcBuf[i + 2];
				i += 2;

				for (count, count > 0; count--;) {
					tmpBuf[pos] = value;
					pos++;
				}
			}
			else
			{
				tmpBuf[pos] = srcBuf[i];
				pos++;
			}
		}
		dstSize = pos;

		uint16_t* dstBuf = new uint16_t[dstSize];
		memcpy(dstBuf, tmpBuf, dstSize);
		return dstBuf;

		return nullptr;
	}

	uint16_t* Chunk::encodeRLE(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
	{
		const int tmpSize = srcSize;

		uint16_t* tmpBuf = new uint16_t[tmpSize];
		int pos = 0;

		for (int i = 0; i < srcSize; i++) 
		{
			int count = 1;

			while (srcBuf[i] == srcBuf[i + 1]) 
			{
				count++;
				i++;
			}
			if (count > 2) 
			{
				//Flag
				tmpBuf[pos] = 0;
				pos++;
				//Count
				tmpBuf[pos] = count;
				pos++;
				//Value
				tmpBuf[pos] = srcBuf[i];
				pos++;
			}
			else 
			{
				for (count; count > 0; count--)
				{
					tmpBuf[pos] = srcBuf[i];
					pos++;
				}
			}
		}
		dstSize = pos;

		uint16_t* dstBuf = new uint16_t[dstSize];
		memcpy(dstBuf, tmpBuf, dstSize);
		return dstBuf;
	}

	unsigned char* Chunk::toByte_lEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
	{
		//Start with bytemode false
		bool byteMode = false;

		//The max size of the result should be size * 2
		const int tmpSize = srcSize * 2;

		//Allocate a temporary array to hold the values.
		unsigned char* tmpBuf = new unsigned char[tmpSize];

		//Keep the current index of the temp array
		int pos = 0;

		for (int i = 0; i < srcSize; i++)
		{
			unsigned char lowBit = srcBuf[i] & 0x00ff;
			unsigned char highBit = srcBuf[i] >> 8;

			//Block for checking mode and setting flags
			if (!byteMode && highBit == 0)
			{
				int count = 1;

				while ((srcBuf[i + count] >> 8) == 0)
				{
					count++;
				}
				if (count > 2)
				{
					//Flag for bytemode true
					byteMode = true;
					tmpBuf[pos] = 0;
					tmpBuf[pos + 1] = 0;
					pos += 2;
				}
			}
			else if (byteMode && highBit != 0)
			{
				byteMode = false;
				//Flag for bytemode false
				tmpBuf[pos] = 0;
				pos++;
			}

			//Block for inserting values according to mode
			if (byteMode)
			{
				tmpBuf[pos] = lowBit;
				pos++;
			}
			else
			{
				tmpBuf[pos] = lowBit;
				tmpBuf[pos + 1] = highBit;
				pos += 2;
			}
		}

		if (pos > tmpSize) {
			throw new runtime_error("Buffer overflow!");
		}

		dstSize = pos;

		unsigned char* dstBuf = new unsigned char[dstSize];
		memcpy(dstBuf, tmpBuf, dstSize);

		return dstBuf;
	}
	unsigned char* Chunk::toByte_bEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
	{
		//Start with bytemode false
		bool byteMode = false;

		//The max size of the result should be size * 2
		const int tmpSize = srcSize * 2;

		//Allocate a temporary array to hold the values.
		unsigned char* tmpBuf = new unsigned char[tmpSize];

		//Keep the current index of the temp array
		int pos = 0;

		for (int i = 0; i < srcSize; i++)
		{
			unsigned char lowBit = srcBuf[i] & 0x00ff;
			unsigned char highBit = srcBuf[i] >> 8;

			//Block for checking mode and setting flags
			if (!byteMode && highBit == 0)
			{
				int count = 1;

				while ((srcBuf[i + count] >> 8) == 0)
				{
					count++;
				}
				if (count > 2)
				{
					//Flag for bytemode true
					byteMode = true;
					tmpBuf[pos] = 0;
					tmpBuf[pos + 1] = 0;
					pos += 2;
				}
			}
			else if (byteMode && highBit != 0)
			{
				byteMode = false;
				//Flag for bytemode false
				tmpBuf[pos] = 0;
				pos++;
			}

			//Block for inserting values according to mode
			if (byteMode)
			{
				tmpBuf[pos] = lowBit;
				pos++;
			}
			else
			{
				tmpBuf[pos] = lowBit;
				tmpBuf[pos + 1] = highBit;
				pos += 2;
			}
		}

		if (pos > tmpSize) {
			throw new runtime_error("Buffer overflow!");
		}

		dstSize = pos;

		unsigned char* dstBuf = new unsigned char[dstSize];
		memcpy(dstBuf, tmpBuf, dstSize);

		return dstBuf;
	}

	unsigned char* Chunk::compressLZMA(unsigned char* srcBuf, size_t srcSize, size_t& dstSize) {

		const int tmpSize = srcSize + ceil(srcSize * 0.01) + 600;
		size_t propSize;

		unsigned char* tmpBuf = new unsigned char[tmpSize];
		unsigned char* props = new unsigned char[LZMA_PROPS_SIZE];

		LzmaCompress(tmpBuf, &dstSize, srcBuf, srcSize, props, &propSize, -1, 0, -1, -1, -1, -1, 2);

		cout << "Chunk compressed to " << dstSize << " bytes. \n";

		unsigned char* dstBuf = new unsigned char[dstSize];
		memcpy(dstBuf, tmpBuf, dstSize);

		delete[]tmpBuf;
		delete[]props;

		return dstBuf;
	}
	unsigned char* Chunk::compressLZ4(unsigned char* srcBuf, size_t srcSize, size_t& dstSize)
	{
		int tmpSrcSize = srcSize;

		char* tmpSrcBuf = new char[srcSize];
		for (int i = 0; i < srcSize; i++)
		{
			tmpSrcBuf[i] = (char)srcBuf[i];
		}

		int tmpDstSize = srcSize + ceil(srcSize * 0.01) + 600;

		char* tmpDstBuf = new char[tmpDstSize];

		dstSize = LZ4_compress_HC(tmpSrcBuf, tmpDstBuf, tmpSrcSize, tmpDstSize, 4);
		cout << "Chunk data compressed to " << dstSize << " bytes." << "\n";

		unsigned char* dstBuf = new unsigned char[dstSize];
		memcpy(dstBuf, tmpDstBuf, dstSize);

		delete[] tmpSrcBuf;
		delete[] tmpDstBuf;
		
		return dstBuf;
	}

	#pragma endregion
}

