#ifndef INC_TEMPERATURE_SENSOR_H_
#define INC_TEMPERATURE_SENSOR_H_

#define MCP9808_REG_TEMP (0x05) // Temperature Register
#define MCP9808_REG_CONF (0x01) // Configuration Register
#define MCP9808_ADDR     (0x30) // MCP9808 base address 0x18<<1

#include "i2c.h"

float TEMP_get_data();

#endif /* INC_TEMPERATURE_SENSOR_H_ */
