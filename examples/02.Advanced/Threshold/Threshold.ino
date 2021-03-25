/**
 * This example contains a setup to start the distance measurement of the VL53L1X with a specific threshold and window.
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

  // Four distance threshold options are available:
  // Below, dataReady becomes high when an object below the Lower threshold has been detected
  // Above, dataReady becomes high when an object above the upper threshold has been detected
  // Out, dataReady becomes high when an object below the Lower threshold OR above the upper threshold has been detected
  // In, dataReady becomes high when an object above the Lower threshold AND below the upper threshold has been detected
  uint16_t LowerThreshold = 150;
  uint16_t UpperThreshold = 250;
  sensor.SetDistanceThreshold(LowerThreshold, UpperThreshold, In); // Detects an object between 150 and 250 mm from the sensor

  uint16_t buffer;
  EThresholdWindow window;
  sensor.GetDistanceThresholdWindow(&window);
  Serial.println("Threshold window: " + String((uint8_t)window));
  sensor.GetDistanceThresholdLow(&buffer);
  Serial.println("Theshold lower: " + String(buffer));
  sensor.GetDistanceThresholdHigh(&buffer);
  Serial.println("Threshold higher: " + String(buffer));

  sensor.StartRanging();
}

void loop() {
  // Checking if data is available. This can also be done through the hardware interrupt. See the ReadDistanceHardwareInterrupt for an example
  uint8_t dataReady = false;
  while(!dataReady) {
    sensor.CheckForDataReady(&dataReady);
    delay(5);
  }

  // Check if the measurement was valid. With a threshold measurement it is possible to get a measurement that didnt 'return' in time. This is also known as a WrapTargetFail
  ERangeStatus rangeStatus;
  sensor.GetRangeStatus(&rangeStatus);

  if (rangeStatus == RangeValid) {
    // Valid measurement so get the results
    uint16_t distance;
    sensor.GetDistanceInMm(&distance);
    Serial.println("Distance in mm: " + String(distance));
  }
  
  // After reading the results reset the interrupt to be able to take another measurement
  sensor.ClearInterrupt();
}