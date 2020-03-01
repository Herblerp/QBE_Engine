#include "config.h"
#include <iostream>

namespace config 
{
	int CHUNK_DIM = 32;
	int MAP_DIM = 1;
	int COMPRESSION_THREAD_COUNT = 6;

	COMPRESSION_ALGORITHM ALGORITHM = COMPRESSION_ALGORITHM::LZMA;
	SYS_ENDIANNESS ENDIANNESS = SYS_ENDIANNESS::LITTLE;
}

bool config::load_config_file(std::string fileName)
{
	int n = 1;
	// little endian if true
	if (*(char*)&n == 1)
	{
		config::ENDIANNESS = SYS_ENDIANNESS::LITTLE;
	}
	else
	{
		config::ENDIANNESS = SYS_ENDIANNESS::BIG;
	}

	//Get values here:
	config::CHUNK_DIM = 32;
	config::MAP_DIM = 5;
	config::COMPRESSION_THREAD_COUNT = 6;

	std::cout << "Config file successfully loaded\n";
	return true;
}
