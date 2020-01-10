#pragma once
#include <cstdint>
#include <vcruntime_string.h>

class rlEncoder
{
public:

	static uint16_t* decodeRLE(uint16_t*, size_t, size_t);
	static uint16_t* encodeRLE(uint16_t*, size_t, size_t&);
private:
	rlEncoder() {}
};

