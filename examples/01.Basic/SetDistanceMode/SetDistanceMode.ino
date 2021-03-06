/**
 * This example contains a basic setup to start the distance measurement of the VL53L1X with different distance modes and timing budgets
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

  // Set the timing budget. Keep in mind these can only be predefined values
  // This is the time that a measurement will take.
  // Allowed values: 15, 20, 33, 50, 100, 200, 500
  sensor.SetTimingBudgetInMs(50); 

  // Read back the Timing Budget
  uint16_t buffer;
  sensor.GetTimingBudgetInMs(&buffer);
  Serial.println("Timing budget: " + String(buffer));

  // Set the intermeasurement period. This should be higher or equal to the timing budget
  // This is the time that is in between measurements when using the sensor in free running mode (default)
  sensor.SetInterMeasurementInMs(50);

  // Read back the intermeasurement time
  sensor.GetInterMeasurementInMs(&buffer);
  Serial.println("Intermeasurement: " + String(buffer));

  // Set the distance mode. This can be Short or Long.
  // Short has better ambient immunity but is only usable up to 1.3m
  // Long can go as far as 4m but needs a higher timing budget and darker environment
  sensor.SetDistanceMode(Short);

  // Read back the distance mode
  EDistanceMode distanceMode; // 1 = Short, 2 = Long
  sensor.GetDistanceMode(&distanceMode);
  Serial.println("Distance mode: " + String((uint16_t)distanceMode));

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