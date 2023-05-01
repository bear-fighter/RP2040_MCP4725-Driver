#include <stdint.h>
#include "mcp4725/rp2040_mcp4725.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define MCP4725_I2C_CHAN 1
#define MCP4725_SDA_PIN 2
#define MCP4725_SCL_PIN 3
#define I2C_BAUD 400000

void main(void) {

    stdio_init_all();

    // Initialize I2C HW block
    i2c_init(i2c1, I2C_BAUD);

    // Setup I2C GPIO Pins
    gpio_set_function(MCP4725_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(MCP4725_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(MCP4725_SDA_PIN);
    gpio_pull_up(MCP4725_SCL_PIN);


}