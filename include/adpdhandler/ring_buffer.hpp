#ifndef _RING_BUFFER
#define _RING_BUFFER

#incdlue <cstdint>

namespace adpd
{
	enum bufferStatus {
		BUFFER_OK,
		BUFFER_FULL,
		BUFFER_EMPTY
	};
	/**
	* A circular Buffer with 255 elements
	*
	*
	*/
	struct circBuffer
	{
		char buffer[255]; //<! The actual buffer 
		uint8_t writeIndex = 0; //index of where to write data from the buffer
		uint8_t readIndex = 0; // index of where to start reading data from the buffer
	};

	bufferStatus writeBuffer(&circBuffer, const char* message);
	bufferStatus readBuffer(&circBuffer, &output, constant uint8_t numChars);
	bufferStatus readLineBuffer(&circBuffer, &output);
}
#endif