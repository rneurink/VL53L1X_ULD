# VL53L1X_ULD

[![Arduino Lint](https://github.com/rneurink/VL53L1X_ULD/actions/workflows/arduino-lint.yml/badge.svg?branch=master)](https://github.com/rneurink/VL53L1X_ULD/actions/workflows/arduino-lint.yml)[![Compile Examples](https://github.com/rneurink/VL53L1X_ULD/actions/workflows/compile-examples.yml/badge.svg?branch=master)](https://github.com/rneurink/VL53L1X_ULD/actions/workflows/compile-examples.yml)

## Summary

This is an Arduino library for interaction with the [VL53L1X](https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html) sensor from [ST](https://www.st.com/content/st_com/en.html). 

This library is built upon the [Ultra Lite Driver API](https://www.st.com/content/st_com/en/products/embedded-software/imaging-software/stsw-img009.html) (STSW-IMG009) from ST and utilizes the I2C protocol to communicate with the sensor.
The manual (UM2510) can be found [here](https://www.st.com/resource/en/user_manual/dm00562924-a-guide-to-using-the-vl53l1x-ultra-lite-driver-stmicroelectronics.pdf) or in the extras folder of this repository.

### Ultra lite driver VS Full API
This library is built upon the Ultra Lite Driver. The ultra lite driver is an optimized version of the previously made [VL53L1x Full API](https://www.st.com/content/st_com/en/products/embedded-software/imaging-software/stsw-img007.html) driver.

There are a few things to look out for, mainly the fast ranging option only works up to 66Hz with the ULD (Ultra Lite Driver) and you can only select from a few timing budget options. However, there is also some gain as the ULD is much smaller in size and integrates the very usefull Dynamic SPAD selection (DSS). In short the DSS tries to make sure your target won't cause under- or overexposure at different distances. See Example->02.Advanced->Extendedinformation to get the amount of SPADs used.
| Differences                  | Full API |         Ultra lite        |
|------------------------------|:--------:|:-------------------------:|
| API Size                     |    9kB   |           2.3kB           |
| Number of files              |    35    |             4             |
| Timing budget                | [20-500] | [15,20,33,50,100,200,500] |
| Fast ranging 100Hz           |    Yes   |       No (66Hz max)       |
| Dynamic SPAD selection (DSS) |    No    |            Yes            |

## Supported platforms

This library should be compatible with all Arduino-compatible board packages where an I2C bus is available

---
### Tested boards/platorms:
- Arduino AVR (Uno, Mega, Nano, Pro Mini, Micro etc.)
- Arduino megaAVR boards (Nano every)
- Adafruit SAMD (SAMD21, SAMD51)
- [MegaCoreX](https://github.com/MCUdude/MegaCoreX) (ATmega4809, ATmega4808, ATmega3209, ATmega3208, ATmega1609, ATmega1608, ATmega809 and ATmega808)
- [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore) (tinyAVR 0-series, tinyAVR 1-series)
- ESP32. The ESP32 needs around 2k2 - 2k7 resistors on the SDA and SCL pins to VCC to work

## Getting started
### Hardware
The VL53L1X sensor itself is not recommended to handsolder unless you're experienced with LGA packages.

Breakout boards:
* [ST nucleo pack](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/imaging-evaluation-boards/p-nucleo-53l1a1.html)
* [ST dual breakout pack](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/imaging-evaluation-boards/vl53l1x-satel.html)
* [ST Expansion board](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/imaging-evaluation-boards/x-nucleo-53l1a1.html)
* [Pimoroni VL53L1X Carrier](https://shop.pimoroni.com/products/vl53l1x-breakout)

If more breakout boards are available please inform me to update the list.

### Software
This library is made to work with the Arduino platform and the [Arduino IDE](https://www.arduino.cc/en/software).

1. In the Arduino IDE, open the 'Sketch' menu and select 'Include Library'm then 'Manage Libraries'
2. Search for VL53L1X_ULD
3. Select the VL53L1x_ULD entry from the list
4. Click 'Install'

Manual installation:

1. Download the [latest release](https://github.com/rneurink/VL53L1X_ULD/releases/latest) source code.
2. Unzip the compressed file.
3. Move the VL53L1X_ULD-VXXX (where VXXX is the Version number) to your libraries folder, which is located in your sketch folder. 
   You can view open your sketch folder location by going to your Arduino IDE and selecting the 'File' menu. After this select the 'Preferences' option and another window will open. In here you can see (and set) your sketchbook location.
4. After the manual installation, restart the Arduino IDE to apply the changes.
