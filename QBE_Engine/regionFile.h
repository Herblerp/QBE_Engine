#pragma once
#include <vector>
#include <stdexcept>
#include "config.h"

using namespace config;

namespace Data {

	class RegionFile
	{
	public:
		RegionFile(Pos _regionPos);
		~RegionFile();

		uint16_t* ReadChunkData(Pos _chunkPos);
		bool SaveChunkData(uint16_t* _chunkData);

	private:

		enum class SystemEndianness{LITTLE, BIG};

		SystemEndianness _systemEndianness;

		Pos _regionPos;
	};
}



