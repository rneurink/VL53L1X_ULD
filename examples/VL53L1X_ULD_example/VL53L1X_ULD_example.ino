#include "VL53L1X_ULD.h"

VL53L1X_ULD sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  VL53L1X_Version_t v = sensor.GetAPIVersion();

  Serial.println("Version: " + String(v.major) + "." + String(v.minor) + "." + String(v.build) + " " + String(v.revision));
}

void loop() {
  // put your main code here, to run repeatedly:

}
