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
  #if defined(__AVR_ATtinyx17__)
  attachInterrupt(digitalPinToInterrupt(17), sw_reset, FALLING);
  #endif

  delay(5000);

  // Wait untill the sensor is fully booted
  uint8_t isBooted = false;
  while (!isBooted) {
    sensor.GetBootState(&isBooted);
    Serial.println("Sensor is not yet booted");
  }
  Serial.println("Sensor is booted");

  // Initialize sensor
  VL53L1_Error status = sensor.Init();
  if (status != VL53L1_ERROR_NONE) {
    Serial.println("Could not initialize device error: " + String(status));
    while (1) {}
  }
  Serial.println("Device initialized");

  // Get the version of the underlying ULD API from ST 
  VL53L1X_Version_t v = sensor.GetAPIVersion();
  Serial.println("Version: " + String(v.major) + "." + String(v.minor) + "." + String(v.build) + " " + String(v.revision));
  
  // Get the sensor ID. Should be 0xEACC
  uint16_t id;
  sensor.GetSensorId(&id);
  Serial.print("Sensor ID: ");
  Serial.println(id, HEX);
  
  // Get the mask revision. Should be 0x10
  uint8_t maskrevision;
  sensor.GetMaskRevision(&maskrevision);
  Serial.print("Sensor Mask revision: ");
  Serial.println(maskrevision, HEX);
  
  // Set a different I2C address
  sensor.SetI2CAddress(0x55);
  Serial.print("New I2C address: 0x");
  Serial.println(sensor.GetI2CAddress(),HEX);

  // Reset the I2C address
  sensor.SetI2CAddress(0x52); // 0x52 is the default address
  Serial.print("New I2C address: 0x");
  Serial.println(sensor.GetI2CAddress(),HEX);

  // Set the interrupt polarity active_low and return it to active_high (default)
  sensor.SetInterruptPolarity(ActiveLOW);
  EInterruptPolarity polarity;
  sensor.GetInterruptPolarity(&polarity);
  Serial.println("Interrupt polarity: " + String((uint8_t)polarity));
  sensor.SetInterruptPolarity(ActiveHIGH);
  sensor.GetInterruptPolarity(&polarity);
  Serial.println("Interrupt polarity: " + String((uint8_t)polarity));

  // Set the timing budget. Keep in mind these can only be predefined values
  uint16_t timingBudget;
  sensor.SetTimingBudgetInMs(50); 
  sensor.GetTimingBudgetInMs(&timingBudget);
  Serial.println("Timing budget: " + String(timingBudget));

  // Set the intermeasurement period. This should be higher or equal to the timing budget
  sensor.SetInterMeasurementInMs(50);
  sensor.GetInterMeasurementInMs(&timingBudget);
  Serial.println("Intermeasurement: " + String(timingBudget));

  // Set the distance mode
  EDistanceMode distanceMode;
  sensor.SetDistanceMode(Short);
  sensor.GetDistanceMode(&distanceMode);
  Serial.println("Distance mode: " + String((uint16_t)distanceMode));

  sensor.StartRanging();

  uint8_t dataReady = false;
  while(!dataReady) {
    sensor.CheckForDataReady(&dataReady);
    delay(5);
  }
  uint16_t buffer, buffer2;
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
  ERangeStatus rangeStatus;
  sensor.GetRangeStatus(&rangeStatus);
  Serial.println("Range status: " + String((uint8_t)rangeStatus));
  VL53L1X_Result_t result;
  sensor.GetResult(&result);
  Serial.println("Result distance: " + String(result.Distance) + " status: " + String(result.Status) + " SPADs: " + String(result.NumSPADs));
  sensor.StopRanging();
  sensor.ClearInterrupt();

  EThresholdWindow window;
  sensor.SetDistanceThreshold(150,200,In);
  sensor.GetDistanceThresholdWindow(&window);
  Serial.println("Threshold window: " + String((uint8_t)window));
  sensor.GetDistanceThresholdLow(&buffer);
  Serial.println("Theshold lower: " + String(buffer));
  sensor.GetDistanceThresholdHigh(&buffer);
  Serial.println("Threshold higher: " + String(buffer));

  sensor.ResetDistanceThreshold(); // set back to default
  sensor.GetDistanceThresholdWindow(&window);
  Serial.println("Threshold window: " + String((uint8_t)window));
  sensor.GetDistanceThresholdLow(&buffer);
  Serial.println("Theshold lower: " + String(buffer));
  sensor.GetDistanceThresholdHigh(&buffer);
  Serial.println("Threshold higher: " + String(buffer));

  sensor.GetROI(&buffer,&buffer2);
  Serial.println("ROI X: " + String(buffer) + " Y: " + String(buffer2));
  sensor.GetROICenter((uint8_t*)&buffer);
  Serial.println("ROI center: " + String((uint8_t)buffer));

  //sensor.StartRanging();
}

void loop() {
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

#if defined(__AVR_ATtinyx17__)
void sw_reset() {
  _PROTECTED_WRITE(RSTCTRL.SWRR,1);
}
  #endif
