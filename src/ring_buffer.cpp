#include "adpdhandler/ring_buffer.hpp"

using namespace adpd;

void writeChar(circBuffer& buffer, char character)
{
	buffer.buffer[buffer.writeIndex] = character;
	buffer.writeIndex = (buffer.writeIndex + 1) % BUFFER_SIZE;
}

bufferStatus adpd::writeBuffer(circBuffer& buffer, const char* message)
{
	int messageOffset = 0;
	char messageChar = *(message + messageOffset);
	while (messageChar != '\0') //while the character is not a null character
	{
		if (bufferFull(buffer))
		{
			//If the buffer is full stop writing the message and return buffer full
			return bufferStatus::BUFFER_FULL;
		}
		else
		{
			writeChar(buffer, messageChar);
		}
		messageOffset += 1; //Increment the message offset
		messageChar = *(message + messageOffset);
	}
	return bufferStatus::BUFFER_OK; //If we wrote everything without error return that the buffer's okay
}

bufferStatus adpd::getBufferStatus(const circBuffer& buffer)
{
	if (bufferFull(buffer))
	{
		return bufferStatus::BUFFER_FULL;
	}
	else if (bufferEmpty(buffer))
	{
		return bufferStatus::BUFFER_EMPTY;
	}
	else
	{
		return bufferStatus::BUFFER_OK;
	}
}

bool adpd::bufferEmpty(const circBuffer& buffer)
{
	return buffer.readIndex == buffer.writeIndex;
}

bool adpd::bufferFull(const circBuffer& buffer)
{
	return (buffer.readIndex - buffer.writeIndex)==1;
}

bufferStatus adpd::readBuffer(circBuffer& buffer,char* message, const uint8_t numChars)
{
	for (int j = 0; j < numChars; j++)
	{
		if (!bufferEmpty(buffer))
		{
			//If the buffer isn't empty, read a byte off and stick it into the message at the appropriate index
			*(message+j) = buffer.buffer[buffer.readIndex];
			buffer.readIndex += 1;
		}
		else return bufferStatus::BUFFER_EMPTY;
	}
	return bufferStatus::BUFFER_OK;
}