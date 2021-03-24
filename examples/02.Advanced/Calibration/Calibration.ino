/**
 * This example contains a basic setup to start the distance measurement of the VL53L1X
 * 
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

  sensor.StartRanging();
}

void loop() {
  // Checking if data is available. This can also be done through the hardware interrupt
  uint8_t dataReady = false;
  while(!dataReady) {
    sensor.CheckForDataReady(&dataReady);
    delay(5);
  }

  // Get the results
  uint16_t distance;
  sensor.GetDistanceInMm(&distance);
  Serial.println("Distance in mm: " + String(distance));
  
  // After reading the results reset the interrupt to be able to take another measurement
  sensor.ClearInterrupt();
}