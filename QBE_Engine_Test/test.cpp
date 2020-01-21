#include "pch.h"
#include "../QBE_Engine_Compression/rlEncoder.h"
#include "../QBE_Engine_Compression/byteEncoder.h"

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