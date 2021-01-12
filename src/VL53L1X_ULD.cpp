
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
 * @brief This function is a combination of GetBootState and Init. It waits for the device to boot up (with a timeout) and initializes it.
 */
VL53L1_Error VL53L1X_ULD::Begin() {
    uint8_t isBooted = false;
    uint16_t startTime = millis();
    while (!isBooted && (millis() < (startTime + 100))) {
        GetBootState(&isBooted);
        delay(5);
    }
    // Check if the device has booted. If not a timeout has occured
    if (!isBooted) {
        return VL53L1_ERROR_TIME_OUT;
    }

    // Initialize the device
    return Init();
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
 * @brief This function sets the timing budget in ms.
 * @param timingBudgetInMs only predefined values are allowed!! 
 * predefined values = 15 ,20 ,33 ,50 ,100 (default),200 ,500 ms
 */
VL53L1_Error VL53L1X_ULD::SetTimingBudgetInMs(uint16_t timingBudgetInMs) {
    VL53L1_Error status = VL53L1_ERROR_NONE;
    switch (timingBudgetInMs) {
        case 15:
        case 20:
        case 33:
        case 50:
        case 100:
        case 200:
        case 500:
            status = VL53L1X_SetTimingBudgetInMs(i2c_address, timingBudgetInMs);
            break;
        default:
            status = VL53L1_ERROR_INVALID_PARAMS;
            break;
    }
    return status;
}

/**
 * @brief This function returns the timing budget in ms
 */
VL53L1_Error VL53L1X_ULD::GetTimingBudgetInMs(uint16_t *timingBudgetInMs) {
    return VL53L1X_GetTimingBudgetInMs(i2c_address, timingBudgetInMs);
}

/**
 * @brief This function sets the distance mode. Short or Long (default)
 * Short mode is limited to 1.3m but has better ambient immunity.
 * Long mode can range up to 4m but needs a darker environment with longer timing budget.
 */
VL53L1_Error VL53L1X_ULD::SetDistanceMode(EDistanceMode mode) {
    return VL53L1X_SetDistanceMode(i2c_address, (uint16_t)mode);
}

/**
 * @brief This function gets the distance mode.
 */
VL53L1_Error VL53L1X_ULD::GetDistanceMode(EDistanceMode *mode) {
    return VL53L1X_GetDistanceMode(i2c_address, (uint16_t*)mode);
}

/**
 * @brief This function sets the time between measurements. This should be equal to or higher than the timing budget. 
 * @param interMeasurementInMs the time between measurements. Is NOT limited to predefined values like the timing budget. defualt is 100ms
 */
VL53L1_Error VL53L1X_ULD::SetInterMeasurementInMs(uint32_t interMeasurementInMs) {
    VL53L1_Error status = VL53L1_ERROR_NONE;
    uint16_t timingBudget;

    status = GetTimingBudgetInMs(&timingBudget);
    if (status != VL53L1_ERROR_NONE) {
        return status;
    }

    if (interMeasurementInMs < timingBudget) {
        return VL53L1_ERROR_INVALID_PARAMS;
    }
    status = VL53L1X_SetInterMeasurementInMs(i2c_address, interMeasurementInMs);
    return status;
}

/**
 * @brief This function gets the time between measurements
 */
VL53L1_Error VL53L1X_ULD::GetInterMeasurementInMs(uint16_t *interMeasurementInMs) {
    return VL53L1X_GetInterMeasurementInMs(i2c_address, interMeasurementInMs);
}

/**
 * @brief This function programs the offset correction in mm
 * @param offset the offset correction value in mm
 */
VL53L1_Error VL53L1X_ULD::SetOffsetInMm(int16_t offset) {
    return VL53L1X_SetOffset(i2c_address, offset);
}

/**
 * @brief This function gets the programmed offset in mm
 */
VL53L1_Error VL53L1X_ULD::GetOffsetInMm(int16_t *offset) {
    return VL53L1X_GetOffset(i2c_address, offset);
}

/**
 * @brief This function programs the xtalk correction value in cps (counts per second).
 * This is the number of photons reflected back from the cover glass in cps
 */
VL53L1_Error VL53L1X_ULD::SetXTalk(uint16_t xTalkValue) {
    return VL53L1X_SetXtalk(i2c_address, xTalkValue);
}

/**
 * @brief This function gets the programmed xtalk correction value in cps 
 */
VL53L1_Error VL53L1X_ULD::GetXTalk(uint16_t *xTalkValue) {
    return VL53L1X_GetXtalk(i2c_address, xTalkValue);
}

/**
 * @brief This function starts the continous ranging distance operation
 * after each measurement the results should be collected and the interrupt should be cleared to allow another measurement
 */
VL53L1_Error VL53L1X_ULD::StartRanging() {
    return VL53L1X_StartRanging(i2c_address);
}

/**
 * @brief This function stops the continous raning distance operation
 */
VL53L1_Error VL53L1X_ULD::StopRanging() {
    return VL53L1X_StopRanging(i2c_address);
}

/**
 * @brief This function checks if new ranging data is available by polling the dedicated register
 * this could also be done by checking the hardware interrupt pin GPIO1
 * @param isDataReady 1: data ready, 0: not ready
 */
VL53L1_Error VL53L1X_ULD::CheckForDataReady(uint8_t *isDataReady) {
    return VL53L1X_CheckForDataReady(i2c_address, isDataReady);
}

/**
 * @brief This function clears the interrupt. This should be called after reading the rangind data
 * to arm the inerrupt for the next data ready event
 */
VL53L1_Error VL53L1X_ULD::ClearInterrupt() {
    return VL53L1X_ClearInterrupt(i2c_address);
}

/**
 * @brief This function gets the measured distance in mm
 */
VL53L1_Error VL53L1X_ULD::GetDistanceInMm(uint16_t *distance) {
    return VL53L1X_GetDistance(i2c_address, distance);
}

/**
 * @brief This function gets the signal per SPAD in kcps/SPAD.
 * kcps stands for Kilo Count Per Second
 */
VL53L1_Error VL53L1X_ULD::GetSignalPerSpad(uint16_t *signalPerSpad) {
    return VL53L1X_GetSignalPerSpad(i2c_address, signalPerSpad);
}

/**
 * @brief This function gets the ambient per SPAD in kcps/SPAD
 */
VL53L1_Error VL53L1X_ULD::GetAmbientPerSpad(uint16_t *ambientPerSpad) {
    return VL53L1X_GetAmbientPerSpad(i2c_address, ambientPerSpad);
}

/**
 * @brief This function gets the returned signal in kcps
 */
VL53L1_Error VL53L1X_ULD::GetSignalRate(uint16_t *signalRate) {
    return VL53L1X_GetSignalRate(i2c_address, signalRate);
}

/**
 * @brief This function gets the ambient rate in kcps
 */
VL53L1_Error VL53L1X_ULD::GetAmbientRate(uint16_t *ambientRate) {
    return VL53L1X_GetAmbientRate(i2c_address, ambientRate);
}

/**
 * @brief This function gets the amount of enabled SPADs
 */
VL53L1_Error VL53L1X_ULD::GetEnabledSpadCount(uint16_t *count) {
    return VL53L1X_GetSpadNb(i2c_address, count);
}

/**
 * @brief This function gets the ranging status
 */
VL53L1_Error VL53L1X_ULD::GetRangeStatus(ERangeStatus *rangeStatus) {
    return VL53L1X_GetRangeStatus(i2c_address, (uint8_t*)rangeStatus);
}

/**
 * @brief This function gets the measurement and range status in a single read.
 * @param result VL53L1X_Result_t struct that contains all necessary info from the measurement reading.
 * contains ranging status, distance, ambient, signal per SPAD and the number of SPADs
 */
VL53L1_Error VL53L1X_ULD::GetResult(VL53L1X_Result_t *result) {
    return VL53L1X_GetResult(i2c_address, result);
}

/**
 * @brief This function programs the threshold detection mode.
 * @param thresLow the lower threshold in mm 
 * @param thresHigh the higher threshold in mm
 * @param window the detection mode. Could be below, above, out and in the detection window.1
 * @return 
 */
VL53L1_Error VL53L1X_ULD::SetDistanceThreshold(uint16_t thresLow, uint16_t thresHigh, EThresholdWindow window, uint8_t IntOnNoTarget) {
    return VL53L1X_SetDistanceThreshold(i2c_address, thresLow, thresHigh, (uint8_t)window, IntOnNoTarget);
}

/**
 * @brief This function resets the threshold detection mode.
 */
VL53L1_Error VL53L1X_ULD::ResetDistanceThreshold() {
    VL53L1_Error status = VL53L1_ERROR_NONE;

    status = VL53L1_WrByte(i2c_address, SYSTEM__INTERRUPT_CONFIG_GPIO, 0x20); // default after reset

    status = VL53L1_WrWord(i2c_address, SYSTEM__THRESH_HIGH, 0);
	status = VL53L1_WrWord(i2c_address, SYSTEM__THRESH_LOW, 0);
    return status;
}

/**
 * @brief This function gets the currently programmed window
 */
VL53L1_Error VL53L1X_ULD::GetDistanceThresholdWindow(EThresholdWindow *window) {
    return VL53L1X_GetDistanceThresholdWindow(i2c_address, (uint16_t*)window);
}

/**
 * @brief This function gets the lower distance threshold value
 */
VL53L1_Error VL53L1X_ULD::GetDistanceThresholdLow(uint16_t *thresLow) {
    return VL53L1X_GetDistanceThresholdLow(i2c_address, thresLow);
}

/**
 * @brief This function gets the upper distance threshold value
 */
VL53L1_Error VL53L1X_ULD::GetDistanceThresholdHigh(uint16_t *thresHigh) {
    return VL53L1X_GetDistanceThresholdHigh(i2c_address, thresHigh);
}

/**
 * @brief This function gets the upper distance threshold value
 */
VL53L1_Error VL53L1X_ULD::SetROI(uint16_t x, uint16_t y) {
    VL53L1_Error status = VL53L1_ERROR_NONE;
    if ((x*y) < 4) {
        status = VL53L1_ERROR_INVALID_PARAMS;
    }
    if (status == VL53L1_ERROR_NONE) {
        status = VL53L1X_SetROI(i2c_address, x, y);
    }
    return status;
}

/**
 * @brief This function gets the upper distance threshold value
 */
VL53L1_Error VL53L1X_ULD::GetROI(uint16_t *x, uint16_t *y) {
    return VL53L1X_GetROI_XY(i2c_address, x, y);
}

/**
 * Table of SPAD locations. Each SPAD has a number which is not obvious.
 *
 * 128,136,144,152,160,168,176,184, 192,200,208,216,224,232,240,248
 * 129,137,145,153,161,169,177,185, 193,201,209,217,225,233,241,249
 * 130,138,146,154,162,170,178,186, 194,202,210,218,226,234,242,250
 * 131,139,147,155,163,171,179,187, 195,203,211,219,227,235,243,251
 * 132,140,148,156,164,172,180,188, 196,204,212,220,228,236,244,252
 * 133,141,149,157,165,173,181,189, 197,205,213,221,229,237,245,253
 * 134,142,150,158,166,174,182,190, 198,206,214,222,230,238,246,254
 * 135,143,151,159,167,175,183,191, 199,207,215,223,231,239,247,255
 * 127,119,111,103, 95, 87, 79, 71, 63, 55, 47, 39, 31, 23, 15, 7
 * 126,118,110,102, 94, 86, 78, 70, 62, 54, 46, 38, 30, 22, 14, 6
 * 125,117,109,101, 93, 85, 77, 69, 61, 53, 45, 37, 29, 21, 13, 5
 * 124,116,108,100, 92, 84, 76, 68, 60, 52, 44, 36, 28, 20, 12, 4
 * 123,115,107, 99, 91, 83, 75, 67, 59, 51, 43, 35, 27, 19, 11, 3
 * 122,114,106, 98, 90, 82, 74, 66, 58, 50, 42, 34, 26, 18, 10, 2
 * 121,113,105, 97, 89, 81, 73, 65, 57, 49, 41, 33, 25, 17, 9, 1
 * 120,112,104, 96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0 
 */

/**
 * @brief This function gets the upper distance threshold value
 */
VL53L1_Error VL53L1X_ULD::SetROICenter(uint8_t center) {
    return VL53L1X_SetROICenter(i2c_address, center);
}

/**
 * @brief This function gets the upper distance threshold value
 */
VL53L1_Error VL53L1X_ULD::GetROICenter(uint8_t *center) {
    return VL53L1X_GetROICenter(i2c_address, center);
}

/**
 * @brief This function programs a new signal threshold in kcps. The default is 1024
 */
VL53L1_Error VL53L1X_ULD::SetSignalThreshold(uint16_t signal) {
    return VL53L1X_SetSignalThreshold(i2c_address, signal);
}

/**
 * @brief This function gets current signal threshold in kcps
 */
VL53L1_Error VL53L1X_ULD::GetSignalThreshold(uint16_t *signal) {
    return VL53L1X_GetSignalThreshold(i2c_address, signal);
}

/**
 * @brief This function programs a new sigma threshold in mm. The default is 15mm
 */
VL53L1_Error VL53L1X_ULD::SetSigmaThreshold(uint16_t sigma) {
    return VL53L1X_SetSigmaThreshold(i2c_address, sigma);
}

/**
 * @brief This function gets the current sigma threshold in mm
 */
VL53L1_Error VL53L1X_ULD::GetSigmaThreshold(uint16_t *sigma) {
    return VL53L1X_GetSigmaThreshold(i2c_address, sigma);
}

/**
 * @brief This function performs the temperature calibration. 
 * It is recommended to call this every time a drift of about 8 deg C has been detected.
 */
VL53L1_Error VL53L1X_ULD::StartTemperatureUpdate() {
    return VL53L1X_StartTemperatureUpdate(i2c_address);
}

/**
 * @brief This function performs the offset calibration.
 * @param targetDistanceInMm target distance in mm. ST recommends 100mm
 * Target reflectance should be grey 17%
 * @param foundOffset the found offset. This offset is programmed into the device on completion
 */
VL53L1_Error VL53L1X_ULD::CalibrateOffset(uint16_t targetDistanceInMm, int16_t *foundOffset) {
    return VL53L1X_CalibrateOffset(i2c_address, targetDistanceInMm, foundOffset);
}

/**
 * @brief This function performs the xtalk calibration
 * @param targetDistanceInMm target distance in mm
 * The target distance : the distance where the sensor start to "under range"\n
 * due to the influence of the photons reflected back from the cover glass becoming strong\n
 * It's also called inflection point\n
 * Target reflectance = grey 17%
 * @param foundXtalk the found xtalk. This value is programmed into the device on completion
 */
VL53L1_Error VL53L1X_ULD::CalibrateXTalk(uint16_t targetDistanceInMm, uint16_t *foundXtalk) {
    return VL53L1X_CalibrateXtalk(i2c_address, targetDistanceInMm, foundXtalk);
}