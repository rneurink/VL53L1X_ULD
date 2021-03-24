/**
 * This example contains a basic setup to start the distance measurement of the VL53L1X
 * with the I2C address changed
 */

#include "VL53L1X_ULD.h"

#define VL53L1X_ULD_I2C_ADDRESS 0x55 // Default address is 0x52

VL53L1X_ULD sensor;

void setup() {
  Serial.begin(115200); // Start the serial port
  Wire.begin(); // Initialize the I2C controller

  // Initialize the sensor, give the special I2C_address to the Begin function
  VL53L1_Error status = sensor.Begin(VL53L1X_ULD_I2C_ADDRESS);
  if (status != VL53L1_ERROR_NONE) {
    // If the sensor could not be initialized print out the error code. -7 is timeout
    Serial.println("Could not initialize the sensor, error code: " + String(status));
    while(1) {}
  }
  Serial.println("Sensor initialized");

  // Set a different I2C address
  // This address is stored as long as the sensor is powered. To revert this change you can unplug and replug the power to the sensor
  sensor.SetI2CAddress(VL53L1X_ULD_I2C_ADDRESS);
  Serial.print("New I2C address: 0x");
  Serial.println(sensor.GetI2CAddress(),HEX);

  sensor.StartRanging();
}

void loop() {
  // Checking if data is available. This can also be done through the hardware interrupt. See the ReadDistanceHardwareInterrupt for an example
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