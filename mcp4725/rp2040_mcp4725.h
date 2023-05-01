#ifndef RP2040_MCP4725_H
#define RP2040_MCP4725_H

// Peripheral Assignment Macro
#ifndef MCP4725_I2C_CHAN
#define MCP4725_I2C_CHAN 1
#define MCP4725_SDA_PIN 2
#define MCP4725_SCL_PIN 3
#endif

#if !defined(MCP4725_SDA_PIN) || !defined(MCP4725_SCL_PIN)
#error "I2C Channel Specified for MCP4725 but SDA/SCL Pins not Defined!"
#endif

#include <stdint.h>
#include <stdbool.h>

#include "hardware/i2c.h"

#define MCP4725_ADDR 1100000
#define MCP4725_BAUD 100000
#define MCP4725_DAC_VALS 4096U
#define MCP4725_DAC_VCC 5.0f
#define MCP4725_NORMMODE 0b00
#define MCP4725_PDMODE 0b10

#define MCP4725_FASTMODECMD 0b00
#define MCP4725_REGCMD 0b010
#define MCP4725_EEPROMCMD 0b011

#define MCP4725_GEN_CALL_ADDR 0b00000000
#define MCP4725_GEN_CALL_RST_CMD 0b00000110

#define MCP4725_TIMEOUT_US 10000

typedef struct mcp4725_data {
    uint8_t     pd      : 2;
    uint16_t    dacval  : 12;
} mcp4725_data;

typedef struct mcp4725 {
    int addr;
    float vset;             // Strictly uni-directional; only populated from device reads
    i2c_inst_t* chan;       // Set only during intialization
    mcp4725_data reg;       // Strictly uni-directional; only populated from device reads
    mcp4725_data eeprom;    // Strictly uni-directional; only populated from device reads
} mcp4725;

// Convert Voltage Setpoint to 12-bit Integer
uint16_t mcp4725_V2Int(float v);

// Convert 12-bit DAC Integer to Voltage
float mcp4725_Int2V(uint16_t val);

// Initialize instance of mcp4725 object
mcp4725 mcp4725_Init(int address, int voltageset, i2c_inst_t* i2c_chan);

// Sends General Call Reset Command (Section 7.3.1)
// Useful for ensuring DAC regsiter is loaded from EEPROM on Startup
void mcp4725_GeneralCallReset(mcp4725* dev);

// Read from EEPROM and DAC Regsiter (Section 6.2)
// Updates data to mcp4725 object passed as agrument
// returns 1 if read is sucessful; returns 0 otherwise
uint8_t mcp4725_Read(mcp4725* dev);

// Fast Mode Write (Section 6.1.1)
void mcp4725_FastWrite(mcp4725* dev, mcp4725_data dat);

// Set Voltage and Transmit
// Reads the voltage back from the device and returns it as a value
float mcp4725_VSet(mcp4725* dev, float volt);

// Write DAC + EEPROM (Section 6.1.2 +Section 6.1.3)
void mcp4725_Write(mcp4725* dev, mcp4725_data dat, bool EEPROM);

#endif