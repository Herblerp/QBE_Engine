#include "chunk.h"
#include <stdexcept>

namespace NS_Data {

	Chunk::Chunk(uint16_t*** _nodeData)
	{
		this->nodeData = _nodeData;
	}
	Chunk::~Chunk()
	{
		//TODO:Clean up
	}
}

