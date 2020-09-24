#include "sensor.h"

// Initializes sensor
bool sensor_init(void) {
	if (HAL_I2C_IsDeviceReady(&hi2c1, SENSOR_ADD, 3, 10) == HAL_OK) {
		if (sensor_read(REG_DEVID) != 0xE5) {
			SENSOR_FAIL = false;
			return false;	
		}

		sensor_write(REG_DATA_FORMAT, 0x01);  // range= +- 4g
		sensor_write(REG_POWER_CTL, 	0x00);  // set standby before wake up
		sensor_write(REG_POWER_CTL, 	0x08);  // set measure and wake up at 8hz		
		SENSOR_FAIL = true;
		return true;
	}
	return false;
}

// Read one register from sensor
uint8_t sensor_read(uint8_t reg) {
	uint8_t buf;
	if (HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADD, 0x00, 1, &buf, 1, 50) == HAL_OK) {
		return buf;
	}
	SENSOR_FAIL = true;
	return 0;
}

// Write one byte data to sensor's register
bool sensor_write(uint8_t reg, uint8_t value) {
	if (HAL_I2C_Mem_Write(&hi2c1, SENSOR_ADD, reg, 1, &value, 1, 50) == HAL_OK) {
		return true;
	}
	SENSOR_FAIL = true;
	return false;
}


// Read sensor acceleration data for x,y,z axis
bool sensor_read_axis_data(void)
{
	if (HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADD, 0x32, 1, (uint8_t *)axis_data, 6, 50) == HAL_OK) {
		return true;
	} else {
		return false;
	}
}

// Set sensor to sleep mode with writing Power Control Register
bool sensor_sleep(void) {
	return sensor_write(REG_POWER_CTL, 0x0C);
}

// Wake up sensor
bool sensor_wakeup(void) {
	if (sensor_write(REG_POWER_CTL, 0x00) == true) {
		return sensor_write(REG_POWER_CTL, 0x08);
	}
	return false;
}

// Convert raw acceleration of axis data to g force 
void convert_raw2g(void) {
	x = ((axis_data[1]<<8)|axis_data[0]);
	y = ((axis_data[3]<<8)|axis_data[2]);
  z = ((axis_data[5]<<8)|axis_data[4]);

  xg = x * 0.0078;
  yg = y * 0.0078;
  zg = z * 0.0078;
	return;
}

float get_xg(void) {
	return xg;
}
float get_yg(void) {
	return yg;
}
float get_zg(void) {
return zg;	
}

// Reinitilazes sensor in case of error or connection lost
void sensor_error_handler(void) {
	sensor_init();
	return;
}

