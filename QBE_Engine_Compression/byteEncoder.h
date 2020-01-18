#pragma once
#include <cstdint>

//! Namespace containing classes used for compression.
namespace Compression {

	/*!	\brief A class that provides methods for performing byte encoding.

		This class should be used to convert between char buffers and uint16_t buffers.
		Runs greater than 2 shorts with a value smaller than 128 will be compressed 
		by dropping the most significant byte. Decoding is done using a system of flags
		encoded into the resulting buffer. Byte encoding is the second step in the compression
		stack for chunk data.
	*/
	class ByteEncoder
	{
	public:

		/*!
			Encodes the given source buffer using byte encoding.
			Must be used on big-endian systems or a runtime error
			will be thrown.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static unsigned char* toByte_bEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Encodes the given source buffer using byte encoding.
			Must be used on little-endian systems or a runtime error
			will be thrown.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static unsigned char* toByte_lEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize);
	};
}