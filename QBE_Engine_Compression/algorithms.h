#pragma once

//! Namespace containing classes used for compression.
namespace Compression {

	/*!	A class that provides methods for performing final compression.

		Use this class as the last step in the compression stack. 
	*/
	class Algorithms
	{
	public:

		/*!
			Compresses the given source buff using the LZMA compression algorithm.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[in,out] dstSize The size of the target buffer, recommended value is max nodes per chunk.
			@return The target buffer.
		*/
		static unsigned char* compressLZMA(unsigned char* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Decompresses the given source buff using the LZMA compression algorithm.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[in,out] dstSize The size of the target buffer, recommended value is max nodes per chunk.
			@return The target buffer.
		*/
		static unsigned char* decompressLZMA(unsigned char* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Compresses the given source buff using the LZ4 compression algorithm.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer.
		*/
		static unsigned char* compressLZ4(unsigned char* srcBuf, size_t srcSize, size_t& dstSize);
	};

}