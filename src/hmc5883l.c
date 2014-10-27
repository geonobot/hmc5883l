/*
 * hmc5883l.c
 *
 *  Created on: 6 oct. 2014
 *      Author: ldo
 *
 * The HMC5883L is a module designed for low-field magnetic sensing with a digital interface.
 * 3-axis magnetoresistive sensors
 * The i2C serial bus allows for easy interface
 */

#include "hmc5883l.h"

double gain = 1090.0; // digital resolution LSB/gauss (default value 1090)

/*
 * \fn void hmc5883l_setup (void)
 * \brief setup measurement mode and sensitivity
 * */
void
hmc5883l_setup (void)
{
  volatile uint8_t buffer[2];

  twi_master_setup (/*SCL_FREQ_100*/);

  /* write Configuration Register A (00)
   * 8 samples averaged, 15 Hz data output rate, normal measurement configuration
   * */
  buffer[0] = CONF_REG_A;
  buffer[1] = _8_SAMPLES + OUTPUT_RATE_15_Hz + NORMAL_MEASUREMENT;
  twi_write_bytes (HMC5883L_ADDRESS, 2, buffer);

  /* write Configuration Register B (01)
   * sensor field range +/- 1.3 Ga (1090 LSB/gauss)
   * */
  buffer[0] = CONF_REG_B;
  buffer[0] = SENSOR_FIELD_RANGE_1300mGa;
  twi_write_bytes (HMC5883L_ADDRESS, 2, buffer);

  gain = SENSITIVITY_1300mGa;

  /* write mode Register (02)
   * continuous-measurement mode
   * */
  buffer[0] = MODE_REG;
  buffer[1] = CONTINUOUS_MODE;
  twi_write_bytes (HMC5883L_ADDRESS, 2, buffer);
}

/*
 * \fn xyz hmc5883l_read_compass_xyz (void)
 * \brief read x,y and z compass value
 * \return x, y and z magnetic field [Ga]
 * */
xyz
hmc5883l_read_compass_xyz (void)
{
  volatile uint8_t reg = DATA_XOUT_H;
  volatile uint8_t buffer[6];
  volatile xyz compass;

  twi_read_bytes (HMC5883L_ADDRESS, &reg, 6, buffer);

  compass.x = ((buffer[0] << 8) + buffer[1]) / gain;
  compass.y = ((buffer[4] << 8) + buffer[5]) / gain;
  compass.z = ((buffer[2] << 8) + buffer[3]) / gain;

  return compass;
}
