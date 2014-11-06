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

static double sensitivity = 1090.0; // digital resolution LSB/gauss (default value 1090)

/*
 * \fn void hmc5883l_setup (void)
 * \brief setup measurement mode and sensitivity
 * */
void
hmc5883l_setup (hmc5883l_measurement_range mr)
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
   * sensor field range */
  buffer[0] = CONF_REG_B;
  switch (mr)
    {
    case MR_880_mGa:
      buffer[1] = SENSOR_FIELD_RANGE_880mGa;
      sensitivity = SENSITIVITY_880mGa;
      break;
    case MR_1900_mGa:
      buffer[1] = SENSOR_FIELD_RANGE_1900mGa;
      sensitivity = SENSITIVITY_1900mGa;
      break;
    case MR_2500_mGa:
      buffer[1] = SENSOR_FIELD_RANGE_2500mGa;
      sensitivity = SENSITIVITY_2500mGa;
      break;
    case MR_4000_mGa:
      buffer[1] = SENSOR_FIELD_RANGE_4000mGa;
      sensitivity = SENSITIVITY_4000mGa;
      break;
    case MR_4700_mGa:
      buffer[1] = SENSOR_FIELD_RANGE_4700mGa;
      sensitivity = SENSITIVITY_4700mGa;
      break;
    case MR_5600_mGa:
      buffer[1] = SENSOR_FIELD_RANGE_5600mGa;
      sensitivity = SENSITIVITY_5600mGa;
      break;
    case MR_8100_mGa:
      buffer[1] = SENSOR_FIELD_RANGE_8100mGa;
      sensitivity = SENSITIVITY_8100mGa;
      break;
    case MR_1300_mGa:
    default:
      buffer[1] = SENSOR_FIELD_RANGE_1300mGa;
      sensitivity = SENSITIVITY_1300mGa;
      break;
    }

  twi_write_bytes (HMC5883L_ADDRESS, 2, buffer);

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
  xyz compass;

  twi_read_bytes (HMC5883L_ADDRESS, &reg, 6, buffer);

  compass.x = (double) ((buffer[0] << 8) + buffer[1]) / sensitivity;
  compass.y = (double) ((buffer[4] << 8) + buffer[5]) / sensitivity;
  compass.z = (double) ((buffer[2] << 8) + buffer[3]) / sensitivity;

  return compass;
}
