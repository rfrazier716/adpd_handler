#include "catch.hpp"
#include "adpdhandler/ring_buffer.hpp"

#include <iostream>

using namespace adpd;
SCENARIO("Creating and Probing a Ring Buffer", "[RingBuffer]")
{
	GIVEN("A Ring Buffer")
	{
		auto buffer = circBuffer{}; //make a new circular buffer
		THEN("Read Index and Write Index should be zero")
		{
			REQUIRE(buffer.readIndex == 0);
			REQUIRE(buffer.writeIndex == 0);
			AND_THEN("bufferFull() should return False")
			{
				REQUIRE(!bufferFull(buffer));
			}
			AND_THEN("bufferEmpty() should return True")
			{
				REQUIRE(bufferEmpty(buffer));
			}
			AND_THEN("bufferStatus() should return BUFFER_EMPTY")
			{
				REQUIRE(getBufferStatus(buffer) == bufferStatus::BUFFER_EMPTY);
			}
		}
		THEN("We Can write a message without error")
		{
			const char * message = "Hello";
			std::cout << buffer.writeIndex << std::endl;
			REQUIRE(writeBuffer(buffer, message) == bufferStatus::BUFFER_OK);
			REQUIRE(buffer.readIndex == 0);
			REQUIRE(buffer.writeIndex == 5);
			AND_THEN("The Message can be read back in pieces")
			{
				auto bytesToRead = 1;
				auto testPassed = true;
				for (int j = 0; j < 5; j++)
				{
					char readByte;
					readBuffer(buffer, &readByte, 1);
					if (readByte != message[j])
					{
						std::cout << readByte << std::endl;
						testPassed = false;
					}
					REQUIRE(testPassed);
				}
			}
		}
	}
}
SCENARIO("Reading From an Empty Buffer", "[RingBuffer]")
{
	GIVEN("An empty Ring Buffer")
	{
		auto buffer = circBuffer{};
		THEN("Reading from the buffer should return BUFFER_EMPTY")
		{
			const int bytesToRead = 5;
			char message[bytesToRead+1]; //Add 1 for the null terminator
			auto status = readBuffer(buffer, message, bytesToRead);
			REQUIRE(status == bufferStatus::BUFFER_EMPTY);
		}
	}
}
SCENARIO("Writing to a Full Buffer", "[RingBuffer]")
{
	GIVEN("An empty Ring Buffer and a message the size of the buffer")
	{
		auto buffer = circBuffer{};
		char message[BUFFER_SIZE]; //Make a message the size of the buffer
		for (int j = 0; j < BUFFER_SIZE - 1; j++)
		{
			message[j] = 'Z';
		}
		message[BUFFER_SIZE - 2] = 'X'; //The final index is X to confirm it was written
		THEN("The Message should write without error")
		{
			auto status = writeBuffer(buffer, message);
			REQUIRE(status == bufferStatus::BUFFER_OK);
			AND_THEN("If we try to write more to the buffer we get BUFFER_FULL")
			{
				REQUIRE(writeBuffer(buffer, message) == bufferStatus::BUFFER_FULL);
			}
		}
	}
}