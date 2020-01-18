#pragma once
namespace Compression {

	class Algorithms
	{
	public:
		static unsigned char* compressLZMA(unsigned char*, size_t, size_t&);
		static unsigned char* compressLZ4(unsigned char*, size_t, size_t&);
	};

}