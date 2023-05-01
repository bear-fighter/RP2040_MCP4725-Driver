cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(RP2040_MCP4725-Driver C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Add library subdirectory
add_subdirectory(mcp4725)

add_executable(${CMAKE_PROJECT_NAME} main.c)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${CMAKE_PROJECT_NAME}
    pico_stdlib
    mcp4725
    hardware_spi
    hardware_gpio
    hardware_pwm
    hardware_irq
    hardware_i2c
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 0)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 1)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})