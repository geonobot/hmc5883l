/*
 * hmc5883l.h
 *
 *  Created on: 6 oct. 2014
 *      Author: ldo
 *
 *      HMC5883L Library
 * The Honeywell HMC5883L is surface-mount, multichip designed for low-field magnetic sensing
 * with a digital interface for applications such as low-cost compassing and magnetometry.
 * The i2c serial bus allows for easy interface.
 * Field range +/- 8 gauss
 */

#ifndef HMC5883L_H_
#define HMC5883L_H_

#include "twi.h"
#include "imu.h"

#define HMC5883L_ADDRESS 0x1E // 7-bits i2c address

/* Register map */
#define CONF_REG_A 0x00
#define CONF_REG_B 0x01
#define MODE_REG 0x02
#define DATA_XOUT_H 0x03
#define DATA_XOUT_L 0x04
#define DATA_ZOUT_H 0x05
#define DATA_ZOUT_L 0x06
#define DATA_YOUT_H 0x07
#define DATA_YOUT_L 0x08

/******************************************************* Configuration register A */
/* number of samples averaged (1 to 8) per measurement output */
#define _1_SAMPLE 0x00 // default
#define _2_SAMPLES 0x20
#define _4_SAMPLES 0x40
#define _8_SAMPLES 0x60

/* data output rate in continuous measurement mode */
#define OUTPUT_RATE_0_75_Hz 0x00
#define OUTPUT_RATE_1_5_Hz 0x04
#define OUTPUT_RATE_3_Hz 0x08
#define OUTPUT_RATE_7_5_Hz 0x0C
#define OUTPUT_RATE_15_Hz 0x10 // default
#define OUTPUT_RATE_30_Hz 0x14
#define OUTPUT_RATE_75_Hz 0x18

/* measurement mode */
#define NORMAL_MEASUREMENT 0x00 // default
#define POSITIVE_BIAS 0x01
#define NEGATIVE_BIAS 0x02

/******************************************************* Configuration register B */
/* sensor field range */
#define SENSOR_FIELD_RANGE_880mGa 0x00
#define SENSOR_FIELD_RANGE_1300mGa 0x20 // default
#define SENSOR_FIELD_RANGE_1900mGa 0x40
#define SENSOR_FIELD_RANGE_2500mGa 0x60
#define SENSOR_FIELD_RANGE_4000mGa 0x80
#define SENSOR_FIELD_RANGE_4700mGa 0xA0
#define SENSOR_FIELD_RANGE_5600mGa 0xC0
#define SENSOR_FIELD_RANGE_8100mGa 0xE0

#define SENSITIVITY_1300mGa 1090.0 // for 1.3Ga, the sensitivity is 1090 LSB/g

/******************************************************* Mode register */
/* Operating mode */
#define CONTINUOUS_MODE 0x00
#define SINGLE_MODE 0x01
#define IDLE_MODE 0x02

void
hmc5883l_setup (void);

xyz
hmc5883l_read_compass_xyz (void);

#endif /* HMC5883L_H_ */
