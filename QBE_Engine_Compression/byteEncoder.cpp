#include "byteEncoder.h"
#include <wchar.h>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace Compression;

unsigned char* ByteEncoder::toChar(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
{
	if (isBigEndian())
	{
		return toChar_bEndian(srcBuf, srcSize, dstSize);
	}
	else
	{
		return toChar_lEndian(srcBuf, srcSize, dstSize);
	}
}
uint16_t* ByteEncoder::toShort(unsigned char* srcBuf, size_t srcSize, size_t& dstSize)
{
	if (isBigEndian())
	{
		return toShort_bEndian(srcBuf, srcSize, dstSize);
	}
	else
	{
		return toShort_lEndian(srcBuf, srcSize, dstSize);
	}
}

bool ByteEncoder::isBigEndian()
{
	int n = 1;
	// little endian if true
	if (*(char*)&n == 1)
	{
		return false;
	}
	return true;
}

unsigned char* ByteEncoder::toChar_lEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
{
	if(isBigEndian)
		throw runtime_error{ "Incompatible endianness." };

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
uint16_t* ByteEncoder::toShort_lEndian(unsigned char* srcBuf, size_t srcSize, size_t& dstSize)
{
	if (!isBigEndian)
		throw runtime_error{ "Incompatible endianness." };

	bool byteMode = false;

	size_t maxSize = srcSize * 2;
	uint16_t* tmpBuf = new uint16_t[maxSize];

	size_t tmpSize = 0;

	for (int i = 0; i < srcSize; i++) {

		//If-block for checking flags
		if (byteMode)
		{
			if (srcBuf[i] == 0)
			{
				byteMode = false;
				i++;
			}
		}
		else
		{
			if (srcBuf[i] == 0 && srcBuf[i + 1] == 0)
			{
				byteMode = true;
				i += 2;
			}
		}

		//If-block for getting values
		if (byteMode)
		{
			unsigned char lowBit = srcBuf[i];
			unsigned char highBit = (unsigned char)0;
			unsigned short y = highBit << 8 | lowBit;

			tmpSize++;
		}
		else
		{
			unsigned char lowBit = srcBuf[i];
			unsigned char highBit = srcBuf[i + 1];
			unsigned short y = highBit << 8 | lowBit;

			i++;
			tmpSize++;
		}
	}
	dstSize = tmpSize;

	uint16_t* dstBuf = new uint16_t[dstSize];
	memcpy(dstBuf, tmpBuf, dstSize);

	return dstBuf;
}

unsigned char* ByteEncoder::toChar_bEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize)
{
	if (!isBigEndian)
		throw runtime_error{ "Incompatible endianness." };

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

		//If-block for checking mode and setting flags
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

		//If-block for inserting values according to mode
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
uint16_t* ByteEncoder::toShort_bEndian(unsigned char* srcBuf, size_t srcSize, size_t& dstSize)
{
	if (!isBigEndian)
		throw runtime_error{ "Incompatible endianness." };

	bool byteMode = false;

	size_t maxSize = srcSize * 2;
	uint16_t* tmpBuf = new uint16_t[maxSize];

	size_t tmpSize = 0;

	for (int i = 0; i < srcSize; i++) {

		//If-block for checking flags
		if (byteMode)
		{
			if (srcBuf[i] == 0)
			{
				byteMode = false;
				i++;
			}
		}
		else
		{
			if (srcBuf[i] == 0 && srcBuf[i + 1] == 0)
			{
				byteMode = true;
				i += 2;
			}
		}

		//If-block for getting values
		if (byteMode)
		{
			unsigned char lowBit = srcBuf[i];
			unsigned char highBit = (unsigned char)0;
			unsigned short y = lowBit << 8 | highBit;

			tmpSize++;
		}
		else
		{
			unsigned char lowBit = srcBuf[i];
			unsigned char highBit = srcBuf[i + 1];
			unsigned short y = lowBit << 8 | highBit;

			i++;
			tmpSize++;
		}
	}
	dstSize = tmpSize;

	uint16_t* dstBuf = new uint16_t[dstSize];
	memcpy(dstBuf, tmpBuf, dstSize);

	return dstBuf;
}


