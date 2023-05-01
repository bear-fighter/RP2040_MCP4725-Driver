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


#define MCP4725_ADDR 1100000
#define NORMMODE 0b00
#define PDMODE 0b10
#define WR_FASTMODECMD 0b000
#define WR_DACCMD 0b010
#define WR_EEPROMCMD 0b011
#define VCC 5f

typedef struct mcp4725_data {
    uint16_t reg;
    uint16_t eeprom;
} mcp4725_data;

typedef struct mcp4725 {
    int addr;
    float vset;
    mcp4725_data data;
} mcp4725;

// Initialize instance of mcp4725 object
mcp4725 mcp4725_Init(int address, int voltageset);

// Read from EEPROM and DAC Regsiter (Section 6.2)
// returns 1 if read is sucessful; returns 0 otherwise
uint8_t mcp4725_Read(mcp4725* dev);

// (NEEDS PROTOTYPE) Fast Mode Write (Section 6.1.1)
void mcp4725_FastWrite(mcp4725* dev, uint8_t pdsel, uint16_t dacval);

// Set Voltage and Transmit
// Reads the voltage back from the device and returns it as a value
float mcp4725_VSet(mcp4725* dev, float volt);

// (NEEDS PROTOTYPE) Write DAC Register (Section 6.1.2)

// (NEEDS PROTOTYPE) Write DAC + EEPROM (Section 6.1.3)

#endif