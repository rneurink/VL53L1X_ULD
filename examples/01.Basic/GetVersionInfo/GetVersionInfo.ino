/**
 * This example contains a simple example to get version information from the API and the sensor
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

  // Get the version of the underlying ULD API from ST 
  VL53L1X_Version_t v = sensor.GetAPIVersion();
  Serial.println("API version: " + String(v.major) + "." + String(v.minor) + "." + String(v.build) + " " + String(v.revision));
  
  // Get the sensor ID. Should be 0xEACC
  uint16_t id;
  sensor.GetSensorId(&id);
  Serial.print("Sensor ID: 0x");
  Serial.println(id, HEX);
  
  // Get the mask revision. Should be 0x10
  uint8_t maskrevision;
  sensor.GetMaskRevision(&maskrevision);
  Serial.print("Sensor Mask revision: 0x");
  Serial.println(maskrevision, HEX);
}

void loop() {
  // put your main code here, to run repeatedly:

}