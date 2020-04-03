#ifndef __VL53L1X_ULD_H
#define __VL53L1X_ULD_H

#include "platform/vl53l1_platform.h"
#include "core/VL53L1X_api.h"

/**
 * 
 * TODO: Fix underlying items
 * - Check and fix error returns
 * - 
 */


/**
 * @brief This class acts as a wrapper around the ULD api from ST
 */
class VL53L1X_ULD 
{
    public:
        VL53L1X_ULD(); // Constructor

        /**
         * Initialisation functions
         */
        VL53L1_Error GetBootState(uint8_t *isBooted); // Returns the boot state of the device
        VL53L1_Error Init(); // Intializes the device

        /**
         * Version functions
         */
        VL53L1X_Version_t GetAPIVersion(); // Gets the version of the implemented API
        VL53L1_Error GetSensorId(uint16_t *id); // Gets the sensor ID in a word as 2 bytes ID + Type. Should return 0xEACC
        VL53L1_Error GetMaskRevision(uint8_t *maskRevision); // Gets the sensor mask revision. Should return 0x10

        /**
         * I2C configuration
         */
        VL53L1_Error SetI2CAddress(uint8_t new_address); // Sets a new i2c address
        uint8_t GetI2CAddress(); // Gets the i2c address of the device

        /**
         * Interrupt configuration
         */
        enum EInterruptPolarity { ActiveLOW, ActiveHIGH };
        VL53L1_Error SetInterruptPolarity(EInterruptPolarity polarity); // Sets the interrupt polarity of GPIO1
        VL53L1_Error GetInterruptPolarity(EInterruptPolarity *polarity); // Gets the interrupt polarity of GPIO1

        /**
         * Ranging configuration
         */ 
        VL53L1_Error SetTimingBudgetInMs(uint16_t timingBudgetInMs); // Sets the timing budget in ms. Only predefined values are allowed
        VL53L1_Error GetTimingBudgetInMs(uint16_t *timingBudgetInMs); // Gets the timing budget in ms
        enum EDistanceMode: uint16_t { Short = 1, Long =2 };
        VL53L1_Error SetDistanceMode(EDistanceMode mode); // Sets the distance mode. Short has higher ambient immunity up to 1.3m. Long can be used up to 4m
        VL53L1_Error GetDistanceMode(EDistanceMode *mode); // Gets the distance mode
        VL53L1_Error SetInterMeasurementInMs(uint32_t interMeasurementInMs); // Sets the time between measurements. Should be >= timingBudget
        VL53L1_Error GetInterMeasurementInMs(uint16_t *interMeasurementInMs); // Gets the time between measurements

        VL53L1_Error SetOffsetInMm(int16_t offset); // Sets the offset correction value in mm
        VL53L1_Error GetOffsetInMm(int16_t *offset); // Gets the offset correction value in mm
        VL53L1_Error SetXTalk(uint16_t xTalkValue); // Sets the xtalk correction value in cps
        VL53L1_Error GetXTalk(uint16_t *xTalkValue); // Gets the xtalk correction value

        /**
         * Ranging functions
         */
        VL53L1_Error StartRanging(); // Starts continuous ranging
        VL53L1_Error StopRanging(); // Stops continuous ranging
        VL53L1_Error CheckForDataReady(uint8_t *isDataReady); // Poll if data is ready (SW). also possible to use the hardware GPIO1
        VL53L1_Error ClearInterrupt(); // Clears the interrupt after a ranging data read

        /**
         * Measurement result functions
         */
        VL53L1_Error GetDistanceInMm(uint16_t *distance); // Gets the measured distance in mm
        VL53L1_Error GetSignalPerSpad(uint16_t *signalPerSpad); // Gets the signal per SPAD in kcps/SPAD
        VL53L1_Error GetAmbientPerSpad(uint16_t *ambientPerSpad); // Gets the ambient per SPAD
        VL53L1_Error GetSignalRate(uint16_t *signalRate); // Gets the returned signal in kcps
        VL53L1_Error GetAmbientRate(uint16_t *ambientRate); // Gets the ambient rate in kcps
        VL53L1_Error GetEnabledSpadCount(uint16_t *count); // Gets the number of enabled SPADs
        enum ERangeStatus: uint8_t { RangeValid, SigmaFail, SignalFail, MinRangeFail, PhaseOutOfLimit, HardwareFail, RangeValidNoWrapCheck, WrapTargetFail};
        VL53L1_Error GetRangeStatus(ERangeStatus *rangeStatus); // Gets the ranging status
        VL53L1_Error GetResult(VL53L1X_Result_t *result); // Gets the measurement and ranging status in a single read

        /**
         * Distance threshold functions
         */
        enum EThresholdWindow: uint8_t { Below, Above, Out, In };
        VL53L1_Error SetDistanceThreshold(uint16_t thresLow, uint16_t thresHigh, EThresholdWindow window);
        VL53L1_Error GetDistanceThresholdWindow(EThresholdWindow *window);
        VL53L1_Error GetDistanceThresholdLow(uint16_t *thresLow);
        VL53L1_Error GetDistanceThresholdHigh(uint16_t *thresHigh);

        /**
         * ROI functions
         */
        VL53L1_Error SetROI(uint16_t x, uint16_t y);
        VL53L1_Error GetROI(uint16_t *x, uint16_t *y);
        VL53L1_Error SetROICenter(uint8_t center);
        VL53L1_Error GetROICenter(uint8_t *center);

        /**
         * Calibration functions
         */
        VL53L1_Error SetSignalThreshold(uint16_t signal);
        VL53L1_Error GetSignalThreshold(uint16_t *signal);
        VL53L1_Error SetSigmaThreshold(uint16_t sigma);
        VL53L1_Error GetSigmaThreshold(uint16_t *sigma);

        VL53L1_Error StartTemperatureUpdate();

        VL53L1_Error CalibrateOffset(uint16_t targetDistanceInMm, uint16_t *foundOffset);
        VL53L1_Error CalibrateXTalk(uint16_t targetDistanceInMm, uint16_t *foundXtalk);

    protected:

    private:
        uint8_t     i2c_address = 0x52;
};

#endif