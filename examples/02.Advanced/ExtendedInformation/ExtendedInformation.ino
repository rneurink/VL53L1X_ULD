/**
 * This example contains a basic setup to start the distance measurement of the VL53L1X
 * with extended information about the measurement
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
  delay(500); // Set a delay of 500ms otherwise the serial monitor will be bombarded with information
  // Checking if data is available. This can also be done through the hardware interrupt. See the ReadDistanceHardwareInterrupt for an example
  uint8_t dataReady = false;
  while(!dataReady) {
    sensor.CheckForDataReady(&dataReady);
    delay(5);
  }

  // Get specific results
  uint16_t buffer;
  sensor.GetDistanceInMm(&buffer);
  Serial.println("Distance in mm: " + String(buffer));
  sensor.GetSignalPerSpad(&buffer);
  Serial.println("Signal per SPAD in kcps: " + String(buffer));
  sensor.GetAmbientPerSpad(&buffer);
  Serial.println("Ambient per SPAD in kcps: " + String(buffer));
  sensor.GetSignalRate(&buffer);
  Serial.println("Signal rate in kcps: " + String(buffer));
  sensor.GetAmbientRate(&buffer);
  Serial.println("Ambient rate in kcps: " + String(buffer));
  sensor.GetEnabledSpadCount(&buffer);
  Serial.println("Enabled SPADs: " + String(buffer));

  // Get the range status. This indicates if the signal is good or some error has occured
  // Some interesting return codes are: 0 = Range Valid (good measurement), 2 = Signal fail (most likely too far away or the target is not reflective enough) 
  ERangeStatus rangeStatus;
  sensor.GetRangeStatus(&rangeStatus);
  Serial.println("Range status: " + String((uint8_t)rangeStatus));

  // Get results as a struct
  VL53L1X_Result_t result;
  sensor.GetResult(&result);
  Serial.println("Result distance: " + String(result.Distance) + " status: " + String(result.Status) + " SPADs: " + String(result.NumSPADs));
  Serial.println();

  // After reading the results reset the interrupt to be able to take another measurement
  sensor.ClearInterrupt();
}