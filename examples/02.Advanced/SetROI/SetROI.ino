/**
 * This example contains a setup to start the distance measurement of the VL53L1X with a specified ROI and/or ROI center enabled
 * Reducing the ROI can be helpfull if theres an object blocking a part of the viewing area of the sensor.
 * This could be an example when using the sensor in a tube like structure and the signal might bounce against the wall and intervere with measurements
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

  /**
   * Table of SPAD locations. Each SPAD has a number which is not obvious.
   *
   * 128,136,144,152,160,168,176,184, 192,200,208,216,224,232,240,248
   * 129,137,145,153,161,169,177,185, 193,201,209,217,225,233,241,249
   * 130,138,146,154,162,170,178,186, 194,202,210,218,226,234,242,250
   * 131,139,147,155,163,171,179,187, 195,203,211,219,227,235,243,251
   * 132,140,148,156,164,172,180,188, 196,204,212,220,228,236,244,252
   * 133,141,149,157,165,173,181,189, 197,205,213,221,229,237,245,253
   * 134,142,150,158,166,174,182,190, 198,206,214,222,230,238,246,254
   * 135,143,151,159,167,175,183,191, 199,207,215,223,231,239,247,255
   * 127,119,111,103, 95, 87, 79, 71, 63, 55, 47, 39, 31, 23, 15, 7
   * 126,118,110,102, 94, 86, 78, 70, 62, 54, 46, 38, 30, 22, 14, 6
   * 125,117,109,101, 93, 85, 77, 69, 61, 53, 45, 37, 29, 21, 13, 5
   * 124,116,108,100, 92, 84, 76, 68, 60, 52, 44, 36, 28, 20, 12, 4
   * 123,115,107, 99, 91, 83, 75, 67, 59, 51, 43, 35, 27, 19, 11, 3
   * 122,114,106, 98, 90, 82, 74, 66, 58, 50, 42, 34, 26, 18, 10, 2
   * 121,113,105, 97, 89, 81, 73, 65, 57, 49, 41, 33, 25, 17, 9, 1
   * 120,112,104, 96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0 
   */

  uint8_t x = 4;
  uint8_t y = 16;

  // Set the ROI rectangle with a minimum size of 4 x 4
  sensor.SetROI(x, y);

  // Set the ROI center SPAD, this should be set according the table above. When your ROI has even rows or columns use the upper right SPAD directly from the center point (default is 199)
  uint16_t centerSPAD = 247;
  sensor.SetROICenter(centerSPAD);

  // Read the ROI and ROI center
  uint16_t buffer, buffer2;
  sensor.GetROI(&buffer,&buffer2);
  Serial.println("ROI X: " + String(buffer) + " Y: " + String(buffer2));
  sensor.GetROICenter((uint8_t*)&buffer);
  Serial.println("ROI center: " + String((uint8_t)buffer));

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