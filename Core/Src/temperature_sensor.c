#include "temperature_sensor.h"

float TEMP_get_data()
{
	char data_write[3];
	char data_read[2];
	float temp;

    HAL_I2C_Mem_Write(&hi2c1, MCP9808_ADDR, MCP9808_REG_TEMP, 1, data_write, 3, 100);
    HAL_I2C_Master_Receive(&hi2c1, MCP9808_ADDR, data_read, 2, 50);

    data_read[0] = data_read[0] & 0x1F;  	// clear flag bits
	if((data_read[0] & 0x10) == 0x10)	 	// negative temperature
	{
		data_read[0] = data_read[0] & 0x0F;
		temp = 256.0f - ((float)data_read[0] * 16.0f + (float)data_read[1] / 16.0f);
	}										// positive temperature
	else
	{
	  	temp = (float)data_read[0] * 16.0f + (float)data_read[1] /16.0f;
	}

	return temp;
}
