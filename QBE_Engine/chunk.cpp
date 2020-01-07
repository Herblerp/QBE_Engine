#include "chunk.h"
#include <stdexcept>

namespace NS_Data {

	Chunk::Chunk(uint16_t* _nodeData)
	{
		this->nodeData = _nodeData;
	}
	Chunk::~Chunk()
	{
		delete[] nodeData;
	}
	char* Chunk::compressChunk(char*)
	{
		return nullptr;
	}
	char* Chunk::decompressChunk(char*)
	{
		return nullptr;
	}

	#pragma region Compression_algorithms

	uint16_t* Chunk::encodeRLE(uint16_t* srcBuf, int srcSize, int& dstSize)
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
		memcpy(tmpBuf, dstBuf, dstSize);
		return dstBuf;
	}

	unsigned char* Chunk::toByte_lEndian(uint16_t* srcBuf, int srcSize, int& dstSize)
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
		dstSize = pos;

		unsigned char* dstBuf = new unsigned char[dstSize];
		memcpy(tmpBuf, dstBuf, dstSize);

		return dstBuf;
	}
	unsigned char* Chunk::toByte_bEndian(uint16_t* srcBuf, int srcSize, int& dstSize)
	{
		//Start with bytemode false
		bool byteMode = false;

		//The max size of the result should be size * 2
		const int maxSize = srcSize * 2;

		//Allocate a temporary array to hold the values.
		unsigned char* tmpBuf = new unsigned char[maxSize];

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
		dstSize = pos;

		unsigned char* dstBuf = new unsigned char[dstSize];
		memcpy(tmpBuf, dstBuf, dstSize);

		return dstBuf;
	}

	unsigned char* Chunk::compressLZMA(unsigned char* srcBuf, int srcSize, int& dstSize) {

		/*const int tmpSize = byteCount + ceil(byteCount * 0.01) + 600;

		unsigned char* tmpBuf = new unsigned char[_dstBufSize];
		unsigned char* props = new unsigned char[LZMA_PROPS_SIZE];

		LzmaCompress(tmpBuf, &_outBufSize, srcBuf, _srcBufSize, props, &_propSize, -1, 0, -1, -1, -1, -1, 2);

		cout << "Chunk compressed to " << _outBufSize << " bytes. \n";

		unsigned char* outBuf = new unsigned char[_outBufSize];
		memcpy(outBuf, tmpBuf, _outBufSize);
		return outBuf;*/
	}

	unsigned char* Chunk::compressLZ4(unsigned char* srcBuf)
	{
		/*char* temp = new char[_srcBufSize];
		for (int i = 0; i < _srcBufSize; i++)
		{
			temp[i] = (char)srcBuf[i];
		}

		char* dstBuf = new char[_dstBufSize];

		_outBufSize = LZ4_compress_HC(temp, dstBuf, _srcBufSize, _dstBufSize, 4);
		cout << "Chunk data compressed to " << _outBufSize << " bytes." << "\n";

		unsigned char* outBuf = new unsigned char[_outBufSize];
		for (int i = 0; i < _outBufSize; i++)
		{
			outBuf[i] = (unsigned char)dstBuf[i];
		}
		delete[] dstBuf;
		return outBuf;*/
	}

	#pragma endregion
}

