#include <string>
#ifndef GLOBALS_H
#define GLOBALS_H

namespace config {

	extern int CHUNK_DIM;
	extern int MAP_DIM;
	extern int COMPRESSION_THREAD_COUNT;

	enum COMPRESSION_ALGORITHM { LZMA, LZ4 };
	extern COMPRESSION_ALGORITHM CHUNK_COMPRESSION_ALGORITHM;

	struct Pos
	{
		int pos_x, pos_y, pos_z;
	};

	bool load_config_file(std::string filename);

};

#endif