#pragma once
#include <cstdint>
#include <vcruntime_string.h>

//! Namespace containing classes used for compression.
namespace Compression {
	/*!	\brief A class that provides methods for performing run-length encoding.
		
		As run-length encoding is the first step of the compression stack,
		the methods accept and return uint16_t*. For converting to char*
		the byteEncoder class should be used.
	*/	
	class RLEncoder
	{
	public:

		/*!
			Decodes the given source buffer using run-length encoding. 

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static uint16_t* decodeRLE(uint16_t* srcBuf, size_t srcSize, size_t& dstSize);

		/*!
			Decodes the given source buffer using run-length encoding.

			@param[in] srcBuf A pointer to the input buffer.
			@param[in] srcSize The size of the source buffer.
			@param[out] dstSize The size of the target buffer.
			@return The target buffer, gets created automatically.
		*/
		static uint16_t* encodeRLE(uint16_t* srcBuf, size_t srcSize, size_t& dstSize);
	private:
		RLEncoder() {}
	};

}