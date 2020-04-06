/**
 * This example contains a basic setup to start the distance measurement of the VL53L1X
 * 
 */

#include "VL53L1X_ULD.h"

VL53L1X_ULD sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Start the serial port
  
  Wire.begin(); // Initialize the I2C controller

  // Initialize the sensor
  VL53L1_Error status = sensor.Begin();
  if (status != VL53L1_ERROR_NONE) {
    // If the sensor could not be initialized print out the error code.
    Serial.println("Could not initialize the sensor, error code: " + String(status));
    while (1) {}
  }
  Serial.println("Sensor initialized");

  sensor.StartRanging();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t dataReady = false;
  while(!dataReady) {
    sensor.CheckForDataReady(&dataReady);
    delay(5);
  }

  VL53L1X_Result_t result;
  sensor.GetResult(&result);
  Serial.println("Result distance: " + String(result.Distance) + " status: " + String(result.Status) + " SPADs: " + String(result.NumSPADs));
  sensor.ClearInterrupt();
}