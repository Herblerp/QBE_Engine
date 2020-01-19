#pragma once
#include <cstdint>

//! Namespace containing classes used for compression.
namespace Compression {

	/*!	A class that provides methods for performing byte encoding.

		This class should be used to convert between char buffers and uint16_t buffers.
		Runs greater than 2 shorts with a value smaller than 128 will be compressed 
		by dropping the most significant byte. Decoding is done using a system of flags
		encoded into the resulting buffer. Byte encoding is the second step in the compression
		stack for chunk data.
	*/
	static class ByteEncoder
	{
	public:

		/*!
			Encodes the given source buffer using byte encoding.

			Determines the endianness of the system and calls the appropriate toChar function.
			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer.
		*/
		static unsigned char* toChar(uint16_t* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Decodes the given source buffer using byte encoding.

			Determines the endianness of the system and calls the appropriate toShort function.
			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer.
		*/
		static uint16_t* toShort(unsigned char* srcBuf, size_t srcSize, size_t& dstSize);

	private:

		/*!
			Private constructor to prevent instantiation.
		*/
		ByteEncoder();

		/*!
			Checks the endianness of the current system.

			@return True if system is big-endian, false if system is little-endian.
		*/
		static bool isBigEndian();

		/*!
			Encodes the given source buffer using byte encoding.
			Must be used on big-endian systems or a runtime error
			will be thrown.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static unsigned char* toChar_bEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Decodes the given source buffer using byte encoding.
			Must be used on big-endian systems or a runtime error
			will be thrown.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static uint16_t* toShort_bEndian(unsigned char* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Encodes the given source buffer using byte encoding.
			Must be used on little-endian systems or a runtime error
			will be thrown.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static unsigned char* toChar_lEndian(uint16_t* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Decodes the given source buffer using byte encoding.
			Must be used on little-endian systems or a runtime error
			will be thrown.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static uint16_t* toShort_lEndian(unsigned char* srcBuf, size_t srcSize, size_t& dstSize);
	};
}