#pragma once
#include <cstdint>
class byteEncoder
{
public:
	static unsigned char* toByte_bEndian(uint16_t*, size_t, size_t&);
	static unsigned char* toByte_lEndian(uint16_t*, size_t, size_t&);
};

