# Spencer Firmware
> The repository for the core firmware that comes preloaded on every Spencer.


Spencer is a DIY voice assistant that talks, lights-up, connects to the internet, and understands simple voice commands. You can learn more [here](https://circuitmess.com/spencer/).

Spencer is also a part of [CircuitMess STEM Box](https://igg.me/at/stem-box/x#/) - a series of fun electronic kits to help children and adults understand the basics of technologies everybody's talking about.


![](https://circuitmess.com/wp-content/uploads/2020/11/spencer-page-1.jpg)


## Development setup

The firmware is based on the [Spencer Library](https://github.com/CircuitMess/Spencer-Library).

Follow the instructions in the [README](https://github.com/CircuitMess/Spencer-Library/blob/master/README.md) on how to install the library, or just clone or download it into your Documents/Arduino/Libraries folder on Windows, or ~/Arduino/libraries folder on Linux. (NOTE: you will have to install some library dependencies.)

To compile and upload you need to have [CMake](https://cmake.org/) and [arduino-cli](https://github.com/arduino/arduino-cli)  installed. You also need to have both of them registered in the PATH.

In the CMakeLists.txt file change the port to your desired COM port (default is /dev/ttyUSB0):
```
set(PORT /dev/ttyUSB0)
```
Then in the root directory of the repository type:
```
mkdir build
cd build
cmake ..
cmake --build . --target CMUpload
```
This should compile and upload the sketch.

## Meta


**CircuitMess**  - https://circuitmess.com/

**Facebook** - https://www.facebook.com/thecircuitmess/

**Instagram** - https://www.instagram.com/thecircuitmess/

**Twitter** - https://twitter.com/circuitmess 

**YouTube** - https://www.youtube.com/channel/UCVUvt1CeoZpCSnwg3oBMsOQ

----
Copyright © 2020 CircuitMess

Licensed under [GPLv3 License](https://www.gnu.org/licenses/gpl-3.0.html).
