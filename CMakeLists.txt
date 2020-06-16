CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

MESSAGE("COMPILE TYPE: ${COMPILE_TYPE}")

if(COMPILE_TYPE STREQUAL "ARMCC")
    #SET(CMAKE_SYSTEM_PROCESSOR arm)
    SET(CMAKE_SYSTEM_NAME Generic)
    SET(CMAKE_CROSSCOMPILING TRUE)

    # force compiler settings
    SET(CMAKE_C_COMPILER_WORKS TRUE)
    SET(CMAKE_CXX_COMPILER_WORKS TRUE)

    # force cmake compilers
    SET(CMAKE_ASM_COMPILER    "arm-none-eabi-gcc")
    SET(CMAKE_C_COMPILER      "arm-none-eabi-gcc")
    SET(CMAKE_CXX_COMPILER    "arm-none-eabi-g++")
    SET(ELF2BIN               "arm-none-eabi-objcopy")

    # set the project names
    SET(PROJECT_NAME "adpd_handler")


    # if the environment does not specify build type, set to Debug
    MESSAGE("Build Type is ${CMAKE_BUILD_TYPE}")

    # here starts the project
    PROJECT("${PROJECT_NAME}" 
            VERSION 0.0
            LANGUAGES C CXX ASM)

    # uncomment below to have a verbose build process
    #SET(CMAKE_VERBOSE_MAKEFILE ON)

    SET(LD_SYS_LIBS "-Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys  -Wl,--end-group")

    SET(CMAKE_C_FLAGS "-std=gnu99 -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fmessage-length=0 -fno-exceptions -fno-builtin -ffunction-sections -fdata-sections -funsigned-char -MMD -fno-delete-null-pointer-checks -fomit-frame-pointer -O0 -g3 -DMBED_DEBUG -DMBED_TRAP_ERRORS_ENABLED=1 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -include mbed_config.h")
    SET(CMAKE_CXX_FLAGS "-std=gnu++11 -fno-rtti -Wvla -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fmessage-length=0 -fno-exceptions -fno-builtin -ffunction-sections -fdata-sections -funsigned-char -MMD -fno-delete-null-pointer-checks -fomit-frame-pointer -O0 -g3 -DMBED_DEBUG -DMBED_TRAP_ERRORS_ENABLED=1 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp  -include mbed_config.h")
    SET(CMAKE_ASM_FLAGS "-x assembler-with-cpp -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fmessage-length=0 -fno-exceptions -fno-builtin -ffunction-sections -fdata-sections -funsigned-char -MMD -fno-delete-null-pointer-checks -fomit-frame-pointer -O0 -g3 -DMBED_DEBUG -DMBED_TRAP_ERRORS_ENABLED=1 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp  -include mbed_config.h")
    SET(CMAKE_CXX_LINK_FLAGS "-Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,__malloc_r -Wl,--wrap,__free_r -Wl,--wrap,__realloc_r -Wl,--wrap,__memalign_r -Wl,--wrap,__calloc_r -Wl,--wrap,exit -Wl,--wrap,atexit -Wl,-n -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp ")
    SET(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} ${LD_SYS_LIBS} -T ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_pp.link_script.ld")

    ADD_DEFINITIONS(
      -DARM_MATH_CM4
      -DDEVICE_ANALOGIN=1
      -DDEVICE_FLASH=1
      -DDEVICE_I2C=1
      -DDEVICE_I2CSLAVE=1
      -DDEVICE_I2C_ASYNCH=1
      -DDEVICE_INTERRUPTIN=1
      -DDEVICE_LPTICKER=1
      -DDEVICE_PORTIN=1
      -DDEVICE_PORTINOUT=1
      -DDEVICE_PORTOUT=1
      -DDEVICE_PWMOUT=1
      -DDEVICE_RTC=1
      -DDEVICE_SERIAL=1
      -DDEVICE_SERIAL_ASYNCH=1
      -DDEVICE_SERIAL_FC=1
      -DDEVICE_SLEEP=1
      -DDEVICE_SPI=1
      -DDEVICE_SPISLAVE=1
      -DDEVICE_SPI_ASYNCH=1
      -DDEVICE_STDIO_MESSAGES=1
      -DDEVICE_USTICKER=1
      -DMBED_BUILD_TIMESTAMP=1582143168.21
      -DTARGET_CORTEX
      -DTARGET_CORTEX_M
      -DTARGET_DEBUG
      -DTARGET_FAMILY_STM32
      -DTARGET_FF_ARDUINO
      -DTARGET_FF_MORPHO
      -DTARGET_LIKE_CORTEX_M4
      -DTARGET_LIKE_MBED
      -DTARGET_M4
      -DTARGET_NUCLEO_F401RE
      -DTARGET_RTOS_M4_M7
      -DTARGET_STM
      -DTARGET_STM32F4
      -DTARGET_STM32F401RE
      -DTARGET_STM32F401xE
      -DTOOLCHAIN_GCC
      -DTOOLCHAIN_GCC_ARM
      -DTRANSACTION_QUEUE_SIZE_SPI=2
      -DUSBHOST_OTHER
      -DUSB_STM_HAL
      -D__CMSIS_RTOS
      -D__CORTEX_M4
      -D__FPU_PRESENT=1
      -D__MBED_CMSIS_RTOS_CM
      -D__MBED__=1
      )

    INCLUDE_DIRECTORIES(
      include/mbed2/targets/TARGET_STM/TARGET_STM32F4/device
      include/mbed2/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F401xE/device
      include/mbed2/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F401xE/TARGET_NUCLEO_F401RE
      include/mbed2/targets/TARGET_STM/TARGET_STM32F4/TARGET_STM32F401xE
      include/mbed2/targets/TARGET_STM/TARGET_STM32F4
      include/mbed2/targets/TARGET_STM
      include/mbed2/platform
      include/mbed2/hal/storage_abstraction
      include/mbed2/hal
      include/mbed2/drivers
      include/mbed2/cmsis/TARGET_CORTEX_M
      include/mbed2/cmsis
      include/mbed2
      include
      )

    # executable mbed2Lib_F401RE
    ADD_EXECUTABLE("${PROJECT_NAME}" ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
    TARGET_LINK_LIBRARIES("${PROJECT_NAME}" ${CMAKE_CURRENT_SOURCE_DIR}/lib/mbedDev_F401RE.a)

    # SET_TARGET_PROPERTIES(mbed2Lib_F401RE PROPERTIES ENABLE_EXPORTS 1)
    # add syslibs dependencies to create the correct linker order
    TARGET_LINK_LIBRARIES("${PROJECT_NAME}" -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys)

     add_custom_command(TARGET "${PROJECT_NAME}" PRE_LINK
                      COMMAND "arm-none-eabi-cpp" -E -P -Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_memalign_r -Wl,--wrap,_calloc_r -Wl,--wrap,exit -Wl,--wrap,atexit -Wl,-n -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp ./STM32F401XE.ld -o ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_pp.link_script.ld
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_pp.link_script.ld"
                      )

    add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD
                       COMMAND ${ELF2BIN} -O ihex $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE:${PROJECT_NAME}>.hex
                       COMMAND ${CMAKE_COMMAND} -E echo "-- built: $<TARGET_FILE:${PROJECT_NAME}>.hex"
                      )

    add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD
                       COMMAND ${ELF2BIN} -O binary $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE:${PROJECT_NAME}>.bin
                       COMMAND ${CMAKE_COMMAND} -E echo "-- built: $<TARGET_FILE:${PROJECT_NAME}>.bin"
                      )

    # If it's a build release copy files to the bin directory
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD

                           COMMAND ${CMAKE_COMMAND} -E copy
                           $<TARGET_FILE:${PROJECT_NAME}>.bin 
                           ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_NAME}.bin

                           COMMAND ${CMAKE_COMMAND} -E echo "-- Copied: $<TARGET_FILE:${PROJECT_NAME}>.bin to /bin"
                          )

        add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD

                           COMMAND ${CMAKE_COMMAND} -E copy
                           $<TARGET_FILE:${PROJECT_NAME}>.hex 
                           ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_NAME}.hex

                           COMMAND ${CMAKE_COMMAND} -E echo "-- Copied: $<TARGET_FILE:${PROJECT_NAME}>.hex to /bin"
                          )
    endif(CMAKE_BUILD_TYPE STREQUAL "Release")

    # Add project.cmake and test.cmake
    IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/project.cmake)
      INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/project.cmake)
    ELSE()
      MESSAGE(STATUS "Add a local project.cmake file to add your own targets.")
    ENDIF()

    # this will take care of binary directories generated by cmake/clion not to confuse the cli build
    FILE(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/.mbedignore" CONTENT "*")
elseif(COMPILE_TYPE STREQUAL "UNIT_TESTS")
    # set to cpp 17 standard
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    PROJECT("Unit Tests" C CXX)
    INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/tests.cmake") 
endif()
