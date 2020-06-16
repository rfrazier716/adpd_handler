#include "adpdhandler/ring_buffer.hpp"

using namespace adpd;

void writeChar(circBuffer& buffer, char character)
{
	buffer.buffer[buffer.writeIndex] = character;
	buffer.writeIndex = (buffer.writeIndex + 1) % BUFFER_SIZE;
}

char readChar(circBuffer& buffer)
{
	char bufferItem = buffer.buffer[buffer.readIndex];
	buffer.readIndex = (buffer.readIndex + 1) % BUFFER_SIZE;
	return bufferItem;
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
	return (buffer.readIndex - buffer.writeIndex)==1 || (buffer.readIndex==0 && buffer.writeIndex==BUFFER_SIZE-1);
}

bufferStatus adpd::writeBuffer(circBuffer& buffer, const char* message)
{
	int messageOffset = 0;
	char messageChar = message[messageOffset];
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
		messageChar = message[messageOffset];
	}
	return bufferStatus::BUFFER_OK; //If we wrote everything without error return that the buffer's okay
}

bufferStatus adpd::readBuffer(circBuffer& buffer,char* message, const uint8_t numChars)
{
	for (int j = 0; j < numChars; j++)
	{
		if (!bufferEmpty(buffer))
		{
			//If the buffer isn't empty, read a byte off and stick it into the message at the appropriate index
			message[j] = readChar(buffer);
		}
		else return bufferStatus::BUFFER_EMPTY;
	}
	return bufferStatus::BUFFER_OK;
}

bufferStatus adpd::readLineBuffer(circBuffer& buffer, char* output, int maxItemsToPull)
{
	//read the buffer until you encount end of line (\r\n) or you've read the max characters
	auto keepPullingData = true;
	auto itemsPulled = 0;
	while(keepPullingData)
	{
		if (!bufferEmpty(buffer))
		{
			//If the buffer isn't empty, read a byte off
			char bufferItem = readChar(buffer);
			if (bufferItem == '\r') //If we pulled a carriage return check if the next character is a line feed
			{
				char nextItem = readChar(buffer);
				if (nextItem == '\n') //If we recieved an end of line
				{
					keepPullingData = false;
				}
				else
				{
					*(output + itemsPulled) = bufferItem;
					itemsPulled += 1;
					*(output + itemsPulled) = nextItem;
					itemsPulled += 1;
				}
			}
			else //if it wasn't a carriage return write it like normal
			{
				*(output + itemsPulled) = bufferItem;
				itemsPulled += 1;
				if (itemsPulled > maxItemsToPull) keepPullingData = false; //If we've pulled the max number of characters stop reading
			}
		}
		else return bufferStatus::BUFFER_EMPTY;
	}
	return bufferStatus::BUFFER_OK;
}