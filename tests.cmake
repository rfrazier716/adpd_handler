 SET(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/library_tests/src")

ADD_DEFINITIONS(
    -DMSVC_X86
    )

INCLUDE_DIRECTORIES(
    include
    test/library_tests
    )

add_library(buffers "src/ring_buffer.cpp")

# ---Tests---
enable_testing() # enable testing for ctest integration

# Adding Catch which manages test routines
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "test")
add_library(catch_main "test/library_tests/catch_main.cpp")


add_executable(testRingBuffer "${TEST_SOURCE_DIR}/test_ring_buffer.cpp")
target_link_libraries(testRingBuffer Catch catch_main buffers)
add_test(NAME RingBuffer COMMAND testRingBuffer)