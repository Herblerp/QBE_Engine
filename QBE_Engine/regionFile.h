#pragma once
#include <vector>
#include "structs.h"

namespace NS_Data {

	class RegionFile
	{
	public:
		RegionFile(Pos _regionPos);
		~RegionFile();

		uint16_t*** ReadChunkData(Pos _chunkPos);
		bool SaveChunkData(uint16_t*** _chunkData);

	private:
		Pos regionPos;
		const int chunkDIM = 128;
	};

}



