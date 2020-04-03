/**
 * @file  vl53l1_i2ccoms.h
 * @brief Contains i2c implementation of the platform
 */
 
#ifndef _VL53L1X_I2CCOMS_H_
#define _VL53L1X_I2CCOMS_H_

#include "vl53l1_types.h"
#include "Arduino.h"
#include "Wire.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief i2c_init() definition.\n
 * 
 */
int8_t i2c_init();

/** @brief i2c_write_multi() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_multi(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t      *pdata,
        uint32_t      count);
/** @brief i2c_read_multi() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_multi(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t      *pdata,
        uint32_t      count);
/** @brief i2c_write_byte() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_byte(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t       data);
/** @brief i2c_write_word() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_word(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint16_t      data);
/** @brief i2c_write_Dword() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_Dword(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint32_t      data);
/** @brief i2c_read_byte() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_byte(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint8_t      *pdata);
/** @brief i2c_read_word() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_word(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint16_t     *pdata);
/** @brief i2c_read_Dword() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_Dword(
        uint8_t       deviceAddress,
        uint16_t      registerAddress,
        uint32_t     *pdata);

#ifdef __cplusplus
}
#endif

#endif
