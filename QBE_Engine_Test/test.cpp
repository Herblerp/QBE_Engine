#include "pch.h"
#include "../QBE_Engine_Compression/rlEncoder.h"

TEST(DataIntegrityTests, rlEncodeDecode) {

    size_t srcSize = 10;
    size_t encodedSize = 0;

    uint16_t myArr[10] = { 1, 1, 1, 1, 1, 1, 2, 2, 1, 5};

    uint16_t* encodedArr = rlEncoder::encodeRLE(myArr, srcSize, encodedSize);
    uint16_t* decodedArr = rlEncoder::decodeRLE(encodedArr, encodedSize, srcSize);

    for (int i = 0; i < srcSize; i++) {
        EXPECT_EQ(myArr[i], decodedArr[i]);
    }
}