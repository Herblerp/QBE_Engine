#include "compression.h"
#include <lz4.h>
#include <lz4hc.h>
#include <LzmaLib.h>
#include <wchar.h>
#include <iostream>


unsigned char* compression::compressLZMA(unsigned char* srcBuf, size_t srcSize, size_t& dstSize) {

	const int tmpSize = srcSize + ceil(srcSize * 0.01) + 600;
	size_t propSize;

	unsigned char* tmpBuf = new unsigned char[tmpSize];
	unsigned char* props = new unsigned char[LZMA_PROPS_SIZE];

	LzmaCompress(tmpBuf, &dstSize, srcBuf, srcSize, props, &propSize, -1, 0, -1, -1, -1, -1, 2);

	std::cout << "Chunk compressed to " << dstSize << " bytes. \n";

	unsigned char* dstBuf = new unsigned char[dstSize];
	memcpy(dstBuf, tmpBuf, dstSize);

	delete[]tmpBuf;
	delete[]props;

	return dstBuf;
}
unsigned char* compression::compressLZ4(unsigned char* srcBuf, size_t srcSize, size_t& dstSize)
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
