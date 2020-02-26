#include "adpdhandler/ring_buffer.hpp"

using namespace adpd;

bufferStatus adpd::writeBuffer(circBuffer& buffer, const char* message)
{
	int messageOffset = 0;
	char messageChar = *(message + messageOffset);
	while (messageChar != '\0') //while the character is not a null character
	{
		if (buffer.readIndex - buffer.writeIndex == 1)
		{
			//If the buffer is full stop writing the message and return buffer full
			return bufferStatus::BUFFER_FULL;
		}
		else
		{
			//Write the character to the buffer
			buffer.buffer[buffer.writeIndex] = messageChar;
			buffer.writeIndex = (buffer.writeIndex+1) % BUFFER_SIZE;
		}
		messageOffset += 1; //Increment the message offset
		messageChar = *(message + messageOffset);
	}
	return bufferStatus::BUFFER_OK; //If we wrote everything without error return that the buffer's okay
}