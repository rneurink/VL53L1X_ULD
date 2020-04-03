/**
 * This example contains a full API test
 * 
 */

#include "VL53L1X_ULD.h"

VL53L1X_ULD sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }
  attachInterrupt(digitalPinToInterrupt(17), sw_reset, FALLING);
  
  delay(5000);

  Wire.begin();
  //Wire.setClock(400000); // use 400 kHz I2C

  uint8_t isBooted;
  while (!isBooted) {
    sensor.GetBootState(&isBooted);
    Serial.println("Sensor is not yet booted");
  }
  Serial.println("Sensor is booted");

  VL53L1_Error status = sensor.Init();
  if (status != VL53L1_ERROR_NONE) {
    Serial.println("Could not initialize device error: " + String(status));
    while (1) {}
  }
  Serial.println("Device initialized");

  VL53L1X_Version_t v = sensor.GetAPIVersion();
  Serial.println("Version: " + String(v.major) + "." + String(v.minor) + "." + String(v.build) + " " + String(v.revision));
  
  uint16_t id;
  sensor.GetSensorId(&id);
  Serial.print("Sensor ID: ");
  Serial.println(id, HEX);
  
  uint8_t maskrevision;
  sensor.GetMaskRevision(&maskrevision);
  Serial.print("Sensor Mask revision: ");
  Serial.println(maskrevision, HEX);
  
  sensor.SetI2CAddress(0x55);
  Serial.print("New I2C address: 0x");
  Serial.println(sensor.GetI2CAddress(),HEX);

  sensor.GetSensorId(&id);
  Serial.print("Sensor ID: ");
  Serial.println(id, HEX);

  sensor.SetI2CAddress(0x52);
  Serial.print("New I2C address: 0x");
  Serial.println(sensor.GetI2CAddress(),HEX);

  sensor.SetInterruptPolarity(VL53L1X_ULD::ActiveLOW);
  VL53L1X_ULD::EInterruptPolarity polarity;
  sensor.GetInterruptPolarity(&polarity);
  Serial.println("Interrupt polarity: " + String((uint8_t)polarity));
  sensor.SetInterruptPolarity(VL53L1X_ULD::ActiveHIGH);
  sensor.GetInterruptPolarity(&polarity);
  Serial.println("Interrupt polarity: " + String((uint8_t)polarity));

  

}

void loop() {
  // put your main code here, to run repeatedly:

}

void sw_reset() {
  _PROTECTED_WRITE(RSTCTRL.SWRR,1);
}
