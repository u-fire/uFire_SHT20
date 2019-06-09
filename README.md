[![GitHub release](https://img.shields.io/github/release/u-fire/Isolated_EC.svg)]()

### Isolated EC Probe Interface

> Monitor hydroponic nutrient levels or salinity in pools.
 - Electrical Conductivity in Siemens (0.5 - 20.0 mS/cm)
 - Total Dissolved Solids in PPM (250 - 100,000 PPM)
 - Salinity in PSU (2 - 12 PSU)
 - Temperature in Celsius/Fahrenheit (-55 - 125 C)
 - Electrically Isolated
 
##### What it is

An electrically isolated I2C sensor device, a waterproof temperature sensor, and an electrical conductivity probe. It measures the conductivity of a solution and converts it into Siemens (S) total dissolved solids and salinity. The firmware allows for single or dual-point calibration with temperature compensation.

The board uses the [Qwiic](https://www.sparkfun.com/qwiic) Connect System for wiring, it's an easy-to-use, polarized, push-to-fit connector. No more mistaken connections or soldering header pins. 

##### Using it

Read the [documentation](https://ufire.co/docs/uFire_EC/) on the [specifications](https://ufire.co/docs/uFire_EC/#characteristics), [setup](https://ufire.co/docs/uFire_EC/#getting-started), and [use](https://ufire.co/docs/uFire_EC/#use) of the device.

The library to use it is in the Arduino and Particle.io IDE. A [python](https://github.com/u-fire/Isolated_EC/tree/master/python/RaspberryPi) and [rust](https://crates.io/crates/ufire_iso_ec) implementation for Raspberry Pi is available. There is also a [MicroPython](https://github.com/u-fire/Isolated_EC/tree/master/python/MicroPython) library.

```
#include <uFire_EC.h>
uFire_EC ec;
ec.measureEC();
```

#### Buy it

Visit [ufire.co](http://ufire.co) and buy a board and probe.
