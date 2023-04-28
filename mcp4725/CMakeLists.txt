cmake_minimum_required(VERSION 3.12)

# Create MPC4275 Library
add_library(
    mcp4725 
    rp2040_mcp4725.h
    rp2040_mcp4725.c
)

target_link_libraries(mcp4725 pico_stdlib hardware_gpio hardware_i2c)