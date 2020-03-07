#include <string>
#ifndef GLOBALS_H
#define GLOBALS_H

namespace config {

	extern int CHUNK_DIM;
	extern int MAP_DIM;
	extern int COMPRESSION_THREAD_COUNT;

	enum COMPRESSION_ALGORITHM { LZMA, LZ4 };
	extern COMPRESSION_ALGORITHM ALGORITHM;

	enum SYS_ENDIANNESS { LITTLE, BIG };
	extern SYS_ENDIANNESS ENDIANNESS;

	bool load_config_file(std::string filename);
};

#endif