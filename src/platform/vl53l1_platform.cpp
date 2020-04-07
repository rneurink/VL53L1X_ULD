
/* 
* This file is part of VL53L1 Platform 
* 
* Copyright (c) 2016, STMicroelectronics - All Rights Reserved 
* 
* License terms: BSD 3-clause "New" or "Revised" License. 
* 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this 
* list of conditions and the following disclaimer. 
* 
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation 
* and/or other materials provided with the distribution. 
* 
* 3. Neither the name of the copyright holder nor the names of its contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
* 
*/

#include "vl53l1_platform.h"
#include "VL53L1X_i2ccoms.h"
#include <string.h>
#include <time.h>
#include <math.h>

#define VL53L1X_MAX_I2C_XFER_SIZE   64 /* Maximum buffer size to be used in i2c */

int8_t VL53L1_WriteMulti(uint16_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int = 0;

    if (count>=VL53L1X_MAX_I2C_XFER_SIZE){
        Status = VL53L1_ERROR_INVALID_PARAMS;
    }

    status_int = i2c_write_multi(deviceAddress, registerAddress, pdata, count);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}

int8_t VL53L1_ReadMulti(uint16_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count){
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    if (count>=VL53L1X_MAX_I2C_XFER_SIZE){
        Status = VL53L1_ERROR_INVALID_PARAMS;
    }

    status_int = i2c_read_multi(deviceAddress, registerAddress, pdata, count);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}

int8_t VL53L1_WrByte(uint16_t deviceAddress, uint16_t registerAddress, uint8_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    status_int = i2c_write_byte(deviceAddress, registerAddress, data);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}

int8_t VL53L1_WrWord(uint16_t deviceAddress, uint16_t registerAddress, uint16_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    status_int = i2c_write_word(deviceAddress, registerAddress, data);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}

int8_t VL53L1_WrDWord(uint16_t deviceAddress, uint16_t registerAddress, uint32_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    status_int = i2c_write_Dword(deviceAddress, registerAddress, data);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}

int8_t VL53L1_RdByte(uint16_t deviceAddress, uint16_t registerAddress, uint8_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    status_int = i2c_read_byte(deviceAddress, registerAddress, data);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}

int8_t VL53L1_RdWord(uint16_t deviceAddress, uint16_t registerAddress, uint16_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    status_int = i2c_read_word(deviceAddress, registerAddress, data);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}

int8_t VL53L1_RdDWord(uint16_t deviceAddress, uint16_t registerAddress, uint32_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    status_int = i2c_read_Dword(deviceAddress, registerAddress, data);

    if (status_int != 0)
        Status = VL53L1_ERROR_CONTROL_INTERFACE;

    return Status;
}
