# Add nonstandard libraries
ADD_LIBRARY(hal_adpd 
src/hal_adpd/adpd_uart.cpp
src/ring_buffer.cpp
)

TARGET_LINK_LIBRARIES(hal_adpd ${CMAKE_CURRENT_SOURCE_DIR}/lib/mbedDev_F401RE.a)

# Link Libraries to main project
TARGET_LINK_LIBRARIES("${PROJECT_NAME}" hal_adpd)