#include "pch.h"
#include "../QBE_Engine_Compression/rlEncoder.h"
#include "../QBE_Engine_Compression/byteEncoder.h"
#include "../QBE_Engine_Compression/algorithms.h"


using namespace Compression;

TEST(DataIntegrityTests, RLEncodeDecode) {

    size_t srcSize = 10;
    size_t encodedSize = 0;
    size_t decodedSize = 0;

    uint16_t myArr[10] = { 1, 1, 1, 1, 1, 2, 2, 2, 1, 5};

    uint16_t* encodedArr = RLEncoder::encodeRLE(myArr, srcSize, encodedSize);
    uint16_t* decodedArr = RLEncoder::decodeRLE(encodedArr, encodedSize, decodedSize);

    EXPECT_EQ(srcSize, decodedSize);

    for (int i = 0; i < srcSize; i++) {
        EXPECT_EQ(myArr[i], decodedArr[i]);
    }
}

TEST(DataIntegrityTests, ByteEncodeDecode) {
    size_t srcSize = 10;
    size_t encodedSize = 0;
    size_t decodedSize = 0;

    uint16_t myArr[10] = { 1, 1, 1, 1, 1000, 1000, 1000, 1, 1, 1000 };

    unsigned char* encodedArr = ByteEncoder::toChar(myArr, srcSize, encodedSize);
    uint16_t* decodedArr = ByteEncoder::toShort(encodedArr, encodedSize, decodedSize);

    EXPECT_EQ(srcSize, decodedSize);

    for (int i = 0; i < srcSize; i++) {
        EXPECT_EQ(myArr[i], decodedArr[i]);
    }
}

TEST(DataIntegrityTests, LZMAcompression) {
    size_t srcSize = pow(32, 3);
    unsigned char* srcBuf = new unsigned char[srcSize];
    for (auto i = 0; i < srcSize; i++) {
        //TODO: Load appropriate node value
        uint16_t x = rand() % 2 + 36;
        srcBuf[i] = x;
    }

    size_t compressedSize = 70000; //should be max chunk dim + a few bytes
    size_t uncompressedSize = 70000;

    unsigned char* compressedBuf = Algorithms::compressLZMA(srcBuf, srcSize, compressedSize);
    unsigned char* uncompressedBuf = Algorithms::decompressLZMA(compressedBuf, compressedSize, uncompressedSize);

    EXPECT_EQ(srcSize, uncompressedSize);

    for (int i = 0; i < uncompressedSize; i++) {
        EXPECT_EQ(uncompressedBuf[i], srcBuf[i]);
    }
}