#ifndef SENSOR
#define SENSOR

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

#include "stdbool.h"

// REGISTERS OF ADXL345
#define REG_DEVID						0x00
#define REG_OFSX 						0x1E
#define REG_OFSY 						0x1F
#define REG_OFSZ 						0x20
#define REG_THRESH_TAP			0x1D
#define REG_DUR           	0x21
#define REG_LATENT        	0x22
#define REG_WINDOW        	0x23
#define REG_THRESH_ACT    	0x24
#define REG_THRESH_INACT  	0x25
#define REG_TIME_INACT    	0x26
#define REG_ACT_INACT_CTL		0x27
#define REG_THRESH_FF				0x28
#define REG_TIME_FF     	  0x29
#define REG_TAP_AXES   	   	0x2A
#define REG_ACT_TAP_STATUS  0x2B
#define REG_BW_RATE         0x2C
#define REG_POWER_CTL       0x2D
#define REG_INT_ENABLE      0x2E
#define REG_INT_MAP         0x2F
#define REG_INT_SOURCE      0x30
#define REG_DATA_FORMAT     0x31
#define REG_DATAX0          0x32
#define REG_DATAX1          0x33
#define REG_DATAY0          0x34
#define REG_DATAY1          0x35
#define REG_DATAZ0          0x36
#define REG_DATAZ1          0x37
#define REG_FIFO_CTL        0x38
#define REG_FIFO_STATUS     0x39



const uint8_t SENSOR_ADD = 0xA7;
bool SENSOR_FAIL = true;

uint8_t axis_data[6];
int16_t x,y,z;
float xg, yg, zg;


bool sensor_init (void);
uint8_t sensor_read(uint8_t reg);
bool sensor_write (uint8_t reg, uint8_t value);
void sensor_error_handler(void);

bool sensor_read_axis_data(void);
void convert_raw2g(void);
float get_xg(void);
float get_yg(void);
float get_zg(void);

bool sensor_sleep(void);
bool sensor_wakeup(void);

#endif
