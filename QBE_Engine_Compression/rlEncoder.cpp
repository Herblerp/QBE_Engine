#include "rlEncoder.h"
#include <iostream>


uint16_t* rlEncoder::encodeRLE(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
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

uint16_t* rlEncoder::decodeRLE(uint16_t* srcBuf, size_t srcSize, size_t dstSize)
{
	uint16_t* tmpBuf = new uint16_t[dstSize];
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
	size_t size = pos;

	if (size != dstSize) {
		throw std::runtime_error("Destination buffsizes must be equal!");
	}

	uint16_t* dstBuf = new uint16_t[size];
	memcpy(dstBuf, tmpBuf, size * 2);

	return dstBuf;
}