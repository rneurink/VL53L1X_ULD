/**
 * This example contains a an example of using 2 sensors on the same I2C bus by using the XSHUT pin of one of the sensors
 */

#include "VL53L1X_ULD.h"

VL53L1X_ULD sensor_1;
VL53L1X_ULD sensor_2;

#define SENSOR_1_XSHUT 3
#define SENSOR_2_I2C_ADDRESS 0x55

void setup() {
  Serial.begin(115200); // Start the serial port
  Wire.begin(); // Initialize the I2C controller

  // Turn off sensor 1 by pulling the XSHUT pin LOW
  pinMode(SENSOR_1_XSHUT, OUTPUT);
  digitalWrite(SENSOR_1_XSHUT, LOW);

  // Initialize sensor 2
  VL53L1_Error status = sensor_2.Begin(SENSOR_2_I2C_ADDRESS);
  if (status != VL53L1_ERROR_NONE) {
    // If the sensor could not be initialized print out the error code. -7 is timeout
    Serial.println("Could not initialize sensor 2, error code: " + String(status));
    while (1) {}
  }
  Serial.println("Sensor initialized");

  // Set the I2C address of sensor 2 to a different address as the default. 
  sensor_2.SetI2CAddress(SENSOR_2_I2C_ADDRESS);

  // Turn on sensor 1 by pulling the XSHUT pin HIGH
  digitalWrite(SENSOR_1_XSHUT, HIGH);

  // Initialize sensor 1
  status = sensor_1.Begin();
  if (status != VL53L1_ERROR_NONE) {
    // If the sensor could not be initialized print out the error code. -7 is timeout
    Serial.println("Could not initialize sensor 1, error code: " + String(status));
    while (1) {}
  }
  Serial.println("Sensor initialized");

  sensor_1.StartRanging();
  sensor_2.StartRanging();
}

void loop() {
  // Checking if data is available. This can also be done through the hardware interrupt
  uint8_t dataReady_sensor_1 = false, dataReady_sensor_2 = false;
  while(!dataReady_sensor_1 || !dataReady_sensor_2) {
    sensor_1.CheckForDataReady(&dataReady_sensor_1);
    sensor_2.CheckForDataReady(&dataReady_sensor_2);
    delay(5);
  }

  // Get the results
  uint16_t distance1, distance2;
  sensor_1.GetDistanceInMm(&distance1);
  sensor_2.GetDistanceInMm(&distance2);
  Serial.println("Distance sensor 1 in mm: " + String(distance1));
  Serial.println("Distance sensor 2 in mm: " + String(distance2));

  // After reading the results reset the interrupt to be able to take another measurement
  sensor_1.ClearInterrupt();
  sensor_2.ClearInterrupt();
}