#include "byteEncoder.h"
#include <wchar.h>
#include <stdexcept>

using namespace Compression;

unsigned char* ByteEncoder::toByte_lEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
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
		throw std::runtime_error("Buffer overflow!");
	}

	dstSize = pos;

	unsigned char* dstBuf = new unsigned char[dstSize];
	memcpy(dstBuf, tmpBuf, dstSize);

	return dstBuf;
}
unsigned char* ByteEncoder::toByte_bEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
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
		unsigned char highBit = srcBuf[i] & 0x00ff;
		unsigned char lowBit = srcBuf[i] >> 8;

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
		throw std::runtime_error("Buffer overflow!");
	}

	dstSize = pos;

	unsigned char* dstBuf = new unsigned char[dstSize];
	memcpy(dstBuf, tmpBuf, dstSize);

	return dstBuf;
}