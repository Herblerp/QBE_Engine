#include "pch.h"
#include "../QBE_Engine_Compression/rlEncoder.h"
#include "../QBE_Engine_Compression/byteEncoder.h"
#include "../QBE_Engine_Compression/algorithms.h"
#include "../QBE_Engine_Data/regionFile.h"


using namespace Compression;
using namespace Data;

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

TEST(DataIntegrityTests, RegionFileRW) {
    
    srand(25);
    int regionSize = 2;
    int chunkSize = 2;
    
    RegionFileInfo regionFileInfo{ regionSize,"testRegion1" };
    RegionFile* regFileW = new RegionFile(regionFileInfo);

    vector<vector<unsigned char>> regionData;
    vector<unsigned char> chunkData;

    for (int chunkCount = 0; chunkCount < pow(regionSize, 3); chunkCount++) {
        chunkData.clear();
        chunkData.reserve(pow(chunkSize, 3));
        for (int nodeCount = 0; nodeCount < pow(chunkSize, 3); nodeCount++)
        {
            chunkData.push_back(rand() % 255);
        }
        regionData.push_back(chunkData);
    }

    int chunkCount = 0;
    for (uint16_t y = 0; y < regionSize; y++) {
        for (uint16_t z = 0; z < regionSize; z++) {
            for (uint16_t x = 0; x < regionSize; x++) {
                regFileW->writeChunkData(regionData.at(chunkCount), ChunkPos{ x, y, z });
                chunkCount++;
            }
        }
    }
    delete regFileW;
    RegionFile* regFileR = new RegionFile(regionFileInfo);

    chunkCount = 0;
    vector<unsigned char> temp;
    for (uint16_t y = 0; y < regionSize; y++) {
        for (uint16_t z = 0; z < regionSize; z++) {
            for (uint16_t x = 0; x < regionSize; x++) {
                temp.clear();
                temp = regFileR->readChunkData(ChunkPos{ x, y, z });
                for (int i = 0; i < temp.size(); i++) {
                    EXPECT_EQ(temp.at(i), regionData.at(chunkCount).at(i));
                }
                chunkCount++;
            }
        }
    }
}