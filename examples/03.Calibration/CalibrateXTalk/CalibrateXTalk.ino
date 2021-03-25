/**
 * This example contains a setup to calibrate the crosstalk or XTalk of the VL53L1X
 */

#include "VL53L1X_ULD.h"

VL53L1X_ULD sensor;

void setup() {
  Serial.begin(115200); // Start the serial port
  Wire.begin(); // Initialize the I2C controller

  // Initialize the sensor
  VL53L1_Error status = sensor.Begin();
  if (status != VL53L1_ERROR_NONE) {
    // If the sensor could not be initialized print out the error code. -7 is timeout
    Serial.println("Could not initialize the sensor, error code: " + String(status));
    while (1) {}
  }
  Serial.println("Sensor initialized");

  // The target distance : the distance where the sensor start to "under range"
  // due to the influence of the photons reflected back from the cover glass becoming strong. It's also called inflection point
  // Target reflectance should be equal to grey 17%
  uint16_t CalibrationDistance = 140;

  // Start the offset calibration
  Serial.println("Place a target, 17 % gray, at " + String(CalibrationDistance) + " mm from the sensor and send something over Serial");
  Serial.readString();
  uint16_t foundXTalk;
  status = sensor.CalibrateXTalk(CalibrationDistance, &foundXTalk);

  Serial.println("Calibrated XTalk: " + String(foundXTalk));
  Serial.println("Remember this value for this sensor with the selected ROI and set it in every sketch to use");
}

void loop() {
  
}