#include "algorithms.h"
#include <lz4.h>
#include <lz4hc.h>
#include <LzmaLib.h>
#include <wchar.h>
#include <iostream>

using namespace Compression;

unsigned char* Algorithms::compressLZMA(unsigned char* srcBuf, size_t srcSize, size_t& dstSize) {

	const int tmpSize = srcSize + ceil(srcSize * 0.01) + 600;
	size_t propSize = LZMA_PROPS_SIZE;

	unsigned char* tmpBuf = new unsigned char[tmpSize];
	unsigned char* props = new unsigned char[LZMA_PROPS_SIZE];

	LzmaCompress(tmpBuf, &dstSize, srcBuf, srcSize, props, &propSize, -1, 0, -1, -1, -1, -1, 2);

	std::cout << "Chunk compressed to " << dstSize << " bytes. \n";

	//Add 5 bytes for the props;
	unsigned char* dstBuf = new unsigned char[dstSize + LZMA_PROPS_SIZE];

	//Copy data
	memcpy(dstBuf, tmpBuf, dstSize);
	
	//Fill remaining bytes with props
	for (int i = 0; i < 5; i++) {
		dstBuf[dstSize + i] = props[i];
	}

	//Set final dest length with props
	dstSize = dstSize + 5;

	delete[]tmpBuf;
	delete[]props;

	return dstBuf;
}
unsigned char* Compression::Algorithms::decompressLZMA(unsigned char* srcBuf, size_t srcSize, size_t& dstSize)
{
	//Initialize prop size and aray
	size_t propSize = LZMA_PROPS_SIZE;
	unsigned char* props = new unsigned char[LZMA_PROPS_SIZE];

	for (int i = 0; i < propSize; i++) {
		props[i] = srcBuf[srcSize - propSize + i];
	}

	//Initialize temp out buf and temp src buf
	size_t tmpSrcSize = srcSize - LZMA_PROPS_SIZE;

	unsigned char* tmpDstBuf = new unsigned char[dstSize];
	unsigned char* tmpSrcBuf = new unsigned char[tmpSrcSize];
	
	//Copy data without props at the end
	memcpy(tmpSrcBuf, srcBuf, tmpSrcSize);

	//Uncompress
	LzmaUncompress(tmpDstBuf, &dstSize, tmpSrcBuf, &tmpSrcSize, props, propSize);

	std::cout << "Chunk uncompressed to " << dstSize << " bytes. \n";

	unsigned char* dstBuf = new unsigned char[dstSize];
	memcpy(dstBuf, tmpDstBuf, dstSize);

	delete[]tmpDstBuf;
	delete[]tmpSrcBuf;
	delete[]props;

	return dstBuf;
}

unsigned char* Algorithms::compressLZ4(unsigned char* srcBuf, size_t srcSize, size_t& dstSize)
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
	std::cout << "Chunk data compressed to " << dstSize << " bytes." << "\n";

	unsigned char* dstBuf = new unsigned char[dstSize];
	memcpy(dstBuf, tmpDstBuf, dstSize);

	delete[] tmpSrcBuf;
	delete[] tmpDstBuf;

	return dstBuf;
}
