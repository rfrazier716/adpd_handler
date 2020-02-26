 SET(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/library_tests/src")

 INCLUDE_DIRECTORIES(
    include/adpdhandler
    test/library_tests
    )

# ---Tests---
enable_testing() # enable testing for ctest integration

# Adding Catch which manages test routines
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "test")
add_library(catch_main "test/library_tests/catch_main.cpp")


add_executable(testRingBuffer "${SOURCE_DIR}/ring_buffer.cpp")
target_link_libraries(testRingBuffer Catch catch_main)
add_test(NAME RingBuffer COMMAND testRingBuffer)