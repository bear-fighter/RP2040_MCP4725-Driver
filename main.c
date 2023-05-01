#include <stdint.h>
#include "mcp4725/rp2040_mcp4725.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define MCP4725_I2C_CHAN 1
#define MCP4725_SDA_PIN 2
#define MCP4725_SCL_PIN 3
#define I2C_BAUD 100000

void main(void) {
    volatile uint8_t data;
    mcp4725 dev1;
    mcp4725_data dat = {0};

    stdio_init_all();

    // Initialize I2C HW block
    i2c_init(i2c1, I2C_BAUD);

    // Setup I2C GPIO Pins
    gpio_set_function(MCP4725_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(MCP4725_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(MCP4725_SDA_PIN);
    gpio_pull_up(MCP4725_SCL_PIN);

    // Init mcp4725 device
    dev1 = mcp4725_Init(MCP4725_ADDR, 1.0, i2c1);

    mcp4725_GeneralCallReset(&dev1);

    dat.pd = MCP4725_NORMMODE;
    dat.dacval = mcp4725_V2Int(4.2069);

    while(1)
    {
        mcp4725_FastWrite(&dev1, dat);
        data = mcp4725_Read(&dev1);

        sleep_ms(500);
    }
}