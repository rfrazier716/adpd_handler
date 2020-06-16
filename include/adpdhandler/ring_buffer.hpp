#ifndef _RING_BUFFER
#define _RING_BUFFER

#define BUFFER_SIZE 10

#ifdef MSVC_X86
//If we're compiling the program for unittests 
#include <cstdint>
#endif

namespace adpd
{	
	enum class bufferStatus {
		BUFFER_OK=0,
		BUFFER_FULL=1,
		BUFFER_EMPTY=2
	};

	/**
	* A circular Buffer with BUFFER_SIZE elements
	*
	*
	*/
	struct circBuffer
	{
		char buffer[BUFFER_SIZE]; //<! The actual buffer 
		uint8_t writeIndex = 0; //index of where to write data from the buffer
		uint8_t readIndex = 0; // index of where to start reading data from the buffer
	};

	bufferStatus getBufferStatus(const circBuffer& buffer);
	bool bufferEmpty(const circBuffer& buffer);
	bool bufferFull(const circBuffer& buffer);

	bufferStatus writeBuffer(circBuffer& buffer, const char* message);
	bufferStatus readBuffer(circBuffer & buffer, char* message, const uint8_t numChars);
	//assumes a linefeed is \r\n
	bufferStatus readLineBuffer(circBuffer & buffer, char* output, int maxItemsToPull=BUFFER_SIZE);
}
#endif