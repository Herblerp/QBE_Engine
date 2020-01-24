#include "config.h"
#include "INIReader.h"
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

	INIReader reader(fileName);

	if (reader.ParseError() != 0) {
		std::cout << "Somthing went wrong when trying to parse " << fileName <<"\n";
		return false;
	}

	//Get values here:
	config::CHUNK_DIM = reader.GetInteger("", "", 32);
	config::MAP_DIM = reader.GetInteger("", "", 5);
	config::COMPRESSION_THREAD_COUNT = reader.GetInteger("", "", 6);

	std::cout << "Config file successfully loaded\n";
	return true;
}
