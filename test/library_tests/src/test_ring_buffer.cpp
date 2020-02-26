#include "catch.hpp"
#include "adpdhandler/ring_buffer.hpp"

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
		}
		THEN("We Can write a message without error")
		{
			REQUIRE(writeBuffer(buffer, "Hello") == bufferStatus::BUFFER_OK);
		}
	}
}