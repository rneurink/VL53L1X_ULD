/**
 * This example contains a setup to calibrate the offset of the VL53L1X
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

  // Start the offset calibration
  Serial.println("Place a target, 17 % gray, at 140 mm from the sensor and send something over Serial");
  Serial.readString();
  int16_t foundOffset;
  status = sensor.CalibrateOffset(140, &foundOffset);

  Serial.println("Calibrated offset: " + String(foundOffset));
  Serial.println("Remember this value for this sensor with the selected ROI and set it in every sketch to use");
}

void loop() {
  
}