#include "globals.h"

namespace globals 
{
	int CHUNK_DIM = 32;
	int MAP_DIM = 5;

	COMPRESSION_ALGORITHM CHUNK_COMPRESSION_ALGORITHM = COMPRESSION_ALGORITHM::LZMA;
}
//TODO: Add config file boolean