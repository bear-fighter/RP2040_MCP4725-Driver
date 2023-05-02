cmake_minimum_required(VERSION 3.12)

# Create MPC4275 Library
add_library(
    mcp4725 
    rp2040_mcp4725.h
    rp2040_mcp4725.c
)

target_include_directories(mcp4725 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(mcp4725 pico_stdlib hardware_gpio hardware_i2c)