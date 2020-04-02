
#include "VL53L1X_ULD.h"

VL53L1X_ULD::VL53L1X_ULD() {
    
}

VL53L1X_Version_t VL53L1X_ULD::GetAPIVersion() {
    VL53L1X_Version_t version;
    VL53L1X_GetSWVersion(&version);

    return version;
}