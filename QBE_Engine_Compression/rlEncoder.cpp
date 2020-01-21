#include "rlEncoder.h"
#include <iostream>

using namespace std;
using namespace Compression;

uint16_t* RLEncoder::encodeRLE(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
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
	memcpy(dstBuf, tmpBuf, dstSize * 2);
	return dstBuf;
}
uint16_t* RLEncoder::decodeRLE(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
{
	//Max dst size, this corresponds to max chunkdim of 64
	size_t maxDstSize = 262.144;
	uint16_t* tmpBuf = new uint16_t[maxDstSize];
	int pos = 0;

	for (int i = 0; i < srcSize; i++)
	{
		if (pos == maxDstSize)
			throw runtime_error{ "Buffer overflow when decoding RLE." };

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
	memcpy(dstBuf, tmpBuf, dstSize * 2);

	return dstBuf;
}