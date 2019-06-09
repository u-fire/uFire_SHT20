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

#### Running this example
From the /rust folder, type `cargo run`. You may run into permission issues and need to run the executable with sudo. `sudo ./target/debug/ufire_ec_bin`. You'll be presented with a `> ` prompt. Type `help` and you'll get a list of commands you can run to perform various tasks with the board like taking an EC or temperature measurement. 


### Get the board
Visit [uFire.co](https://ufire.co).