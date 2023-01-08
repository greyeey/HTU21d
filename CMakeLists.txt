cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_HTU21d C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_HTU21d_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

if (TARGET tinyusb_device)
        add_executable(HTU21d_example
                HTU21d_example.c
                )

        # pull in common dependencies
        target_link_libraries(HTU21d_example PUBLIC pico_stdlib hardware_i2c)
        target_include_directories(HTU21d_example PUBLIC
                                ${CMAKE_CURRENT_LIST_DIR})

        # enable usb output, disable uart output
        pico_enable_stdio_usb(HTU21d_example 1)
        #pico_enable_stdio_uart(HTU21d_example 0)

        # create map/bin/hex file etc.
        pico_add_extra_outputs(HTU21d_example)
elseif(PICO_ON_DEVICE)
        message(WARNING "not building HTU21d_example because TinyUSB submodule is not initialized in the SDK")
endif()