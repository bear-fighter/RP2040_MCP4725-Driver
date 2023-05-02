#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "rp2040_mcp4725.h"

uint16_t mcp4725_V2Int(float v) {
    return (uint16_t) (MCP4725_DAC_VALS * (v/MCP4725_DAC_VCC));
}

float mcp4725_Int2V(uint16_t val) {
    return MCP4725_DAC_VCC * ((float) val / (float) MCP4725_DAC_VALS);
}

MCP4725 mcp4725_Init(int address, int voltageset, i2c_inst_t* i2c_chan) {
    mcp4725_data dummydata = {0};
    MCP4725 dev = {.addr = address, .chan = i2c_chan, .reg = dummydata, .eeprom = dummydata, .vset = voltageset};

    return dev;
}

void mcp4725_GeneralCallReset(MCP4725* dev) {
    uint8_t msg = MCP4725_GEN_CALL_RST_CMD;
    i2c_write_timeout_us(dev->chan, MCP4725_GEN_CALL_ADDR, &msg, 1, true, MCP4725_TIMEOUT_US);
}

uint8_t mcp4725_Read(MCP4725* dev) {
    uint8_t rec_bytes[5] = {0};

    i2c_read_timeout_us(dev->chan, dev->addr, rec_bytes, 5, true, MCP4725_TIMEOUT_US);

    dev->reg.pd = rec_bytes[0] >> 1;
    dev->reg.dacval = (rec_bytes[1] << 4) | (rec_bytes[2] >> 4);

    dev->eeprom.pd = rec_bytes[3] >> 5;
    dev->eeprom.dacval = (rec_bytes[3] << 8) | (rec_bytes[4]);

    return 1;
}

void mcp4725_FastWrite(MCP4725* dev, mcp4725_data dat) {
    uint8_t send_bytes[4] = {0};

    send_bytes[0] |= MCP4725_FASTMODECMD << 6;
    send_bytes[0] |= dat.pd << 4;

    send_bytes[0] |= dat.dacval >> 8;

    send_bytes[1] |= dat.dacval << 4;

    send_bytes[2] = send_bytes[0];
    send_bytes[3] = send_bytes[1];

    i2c_write_timeout_us(dev->chan, dev->addr, send_bytes, 4, true, MCP4725_TIMEOUT_US);
}

void mcp4725_Write(MCP4725* dev, mcp4725_data dat, bool EEPROM) {
    uint8_t send_bytes[6] = {0};
    uint8_t wcmd;

    if (EEPROM) wcmd = MCP4725_EEPROMCMD;
    else wcmd = MCP4725_REGCMD;

    send_bytes[0] |= wcmd << 5;
    send_bytes[0] |= dat.pd << 1;

    send_bytes[1] |= dat.dacval >> 4;

    send_bytes[2] |= dat.dacval << 4;

    send_bytes[3] = send_bytes[0];
    send_bytes[4] = send_bytes[1];
    send_bytes[5] = send_bytes[2];

    i2c_write_timeout_us(dev->chan, dev->addr, send_bytes, 6, true, MCP4725_TIMEOUT_US);
}