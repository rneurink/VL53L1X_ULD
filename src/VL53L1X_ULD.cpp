
#include "VL53L1X_ULD.h"

/**
 * @brief This function instantiates the class object
 */
VL53L1X_ULD::VL53L1X_ULD() {
    
}

/**
 * @brief This function gets the boot state of the devices
 * @param isBooted 1:booted, 0:not booted
 */
VL53L1_Error VL53L1X_ULD::GetBootState(uint8_t *isBooted) {
    return VL53L1X_BootState(i2c_address, isBooted);
}

/**
 * @brief This function initializes the device
 */
VL53L1_Error VL53L1X_ULD::Init() {
    return VL53L1X_SensorInit(i2c_address);;
}

/**
 * @brief This function gets the version info from the implemented ULD API from ST
 * @return The version of the implemented API as a VL53L1X_Version_t struct
 */
VL53L1X_Version_t VL53L1X_ULD::GetAPIVersion() {
    VL53L1X_Version_t version;
    VL53L1X_GetSWVersion(&version);

    return version;
}

/**
 * @brief This function reads the sensors' model id and type. Should contain 0xEACC
 */
VL53L1_Error VL53L1X_ULD::GetSensorId(uint16_t *id) {
    return VL53L1X_GetSensorId(i2c_address, id);
}

/**
 * @brief This function reads the sensors' mask revision. Should contain 0x10
 */
VL53L1_Error VL53L1X_ULD::GetMaskRevision(uint8_t *maskRevision) { 
    return VL53L1_RdByte(i2c_address, 0x0111, maskRevision);
}

/**
 * @brief This function sets the sensor I2C address. This can be used to connect multiple devices
 * @param new_address The new address
 */
VL53L1_Error VL53L1X_ULD::SetI2CAddress(uint8_t new_address) {
    VL53L1_Error status = VL53L1_ERROR_NONE;
    
    status = VL53L1X_SetI2CAddress(i2c_address, new_address);
    
    if (status == VL53L1_ERROR_NONE) {
        i2c_address = new_address;
    }
    
    return status;
}

/**
 * @brief This function returns the I2C address of the device
 */
uint8_t VL53L1X_ULD::GetI2CAddress() {
    return i2c_address;
}

/**
 * @brief This function sets the interrupt polarity of GPIO1
 */
VL53L1_Error VL53L1X_ULD::SetInterruptPolarity(EInterruptPolarity polarity) {
    return VL53L1X_SetInterruptPolarity(i2c_address, (uint8_t)polarity);
}

/**
 * @brief This function gets the interrupt polarity of GPIO1
 */
VL53L1_Error VL53L1X_ULD::GetInterruptPolarity(EInterruptPolarity *polarity) {
    return VL53L1X_GetInterruptPolarity(i2c_address, (uint8_t*)polarity);
}



/**
 * @brief 
 * @param 
 * @return 
 */