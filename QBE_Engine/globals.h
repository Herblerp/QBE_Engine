#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {

	extern int CHUNK_DIM;
	extern int MAP_DIM;

	enum COMPRESSION_ALGORITHM { LZMA, LZ4 };
	extern COMPRESSION_ALGORITHM CHUNK_COMPRESSION_ALGORITHM;

	struct Pos
	{
		int pos_x, pos_y, pos_z;
	};
};

#endif