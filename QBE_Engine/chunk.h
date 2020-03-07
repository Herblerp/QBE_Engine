#pragma once
#include <string>
#include <vector>
#include "config.h"
#include <bitset>
#include "globals.h"

using namespace std;
using namespace globals;

namespace Data {

	class Chunk
	{
	public:
		Chunk(uint16_t* nodeData);
		~Chunk();

		char* serialize();
		void deSerialize(char *);

	private:
		Pos chunkPos;
		Pos regionPos;
		uint16_t* nodeData;
	};
}

