/**
 * This example contains a basic setup to start the distance measurement of the VL53L1X with hardware interrupts
 * In comparison to the ReadDistance example. This example uses a hardware interrupt to read the data when available.
 * This makes it possible to put other code in the loop to run. 
 */

#include "VL53L1X_ULD.h"

#define VL53L1X_GPIO1 2 // Connect GPIO1 of the sensor to pin 2 of the arduino. Change this value if another pin is used
bool dataReady;

VL53L1X_ULD sensor;

void setup() {
  Serial.begin(115200); // Start the serial port
  Wire.begin(); // Initialize the I2C controller

  // Set the pin to INPUT as it will be used as an interrupt
  // Technically not nedded as all pins will be defined as inputs on reset
  pinMode(VL53L1X_GPIO1, INPUT);

  // Initialize the sensor
  VL53L1_Error status = sensor.Begin();
  if (status != VL53L1_ERROR_NONE) {
    // If the sensor could not be initialized print out the error code. -7 is timeout
    Serial.println("Could not initialize the sensor, error code: " + String(status));
    while (1) {}
  }
  Serial.println("Sensor initialized");

  // It is also possible to change the interrupt polarity of the sensor.
  // By default it is ActiveHIGH which means the pin will go HIGH when a measurement is done
  
  // If you want to reverse the polarity to ActiveLOW uncomment the following line and change the attachInterrupt from RISING to FALLING
  //sensor.SetInterruptPolarity(ActiveLOW); // Possible values are ActiveHIGH and ActiveLOW
  
  // Read out the interrupt polarity
  EInterruptPolarity polarity; // 0 = ActiveLow, 1 = ActiveHigh
  sensor.GetInterruptPolarity(&polarity);
  Serial.println("Interrupt polarity: " + String((uint8_t)polarity));

  // Attach the hardware interrupt to a method (ReadData) and specify the trigger.
  // For more information about interrupts: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/ 
  attachInterrupt(digitalPinToInterrupt(VL53L1X_GPIO1), ReadData, RISING);

  sensor.StartRanging();
}

void loop() {
  if (dataReady) {
    // Get the results
    uint16_t distance;
    sensor.GetDistanceInMm(&distance);

    // After reading the results reset the interrupt to be able to take another measurement
    sensor.ClearInterrupt();
    dataReady = false;

    Serial.println("Distance in mm: " + String(distance));
  }
}

// This function runs everytime the sensor has data available
void ReadData() {
  dataReady = true;
}
