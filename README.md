# Spencer Firmware
> The repository for the core firmware that comes preloaded on every Spencer.


Spencer is a DIY voice assistant that talks, lights-up, connects to the internet, and understands simple voice commands. You can learn more [here](https://circuitmess.com/spencer/).

Spencer is also a part of [CircuitMess STEM Box](https://igg.me/at/stem-box/x#/) - a series of fun electronic kits to help children and adults understand the basics of technologies everybody's talking about.


![](https://circuitmess.com/wp-content/uploads/2020/11/spencer-page-1.jpg)


# Compiling

The firmware is based on the [Spencer Library](https://github.com/CircuitMess/Spencer-Library). It is, along other required libraries, automatically installed when you install the CircuitMess ESP32 Arduino platform. More info on [CircuitMess/Arduino-Packages](https://github.com/CircuitMess/Arduino-Packages).

## Using Arduino IDE

Simply open Spencer.ino using Arduino IDE, set the board to Spencer, and compile.

## Using CMake

To compile and upload you need to have [CMake](https://cmake.org/) and [arduino-cli](https://github.com/arduino/arduino-cli)  installed. You also need to have both of them registered in the PATH.

In the CMakeLists.txt file change the port to your desired COM port (default is /dev/ttyUSB0) and path to Arduino15 libraries:
```
set(PORT /dev/ttyUSB0)
```
Then in the root directory of the repository type:
```
mkdir cmake
cd cmake
cmake ..
cmake --build . --target CMBuild
```
This will compile the binaries, and place the .bin and .elf files in the build/ directory located in the root of the repository.

To compile the binary, and upload it according to the port set in CMakeLists.txt, run

```cmake --build . --target CMUpload```

in the cmake directory.

# Meta


**CircuitMess**  - https://circuitmess.com/

**Facebook** - https://www.facebook.com/thecircuitmess/

**Instagram** - https://www.instagram.com/thecircuitmess/

**Twitter** - https://twitter.com/circuitmess 

**YouTube** - https://www.youtube.com/channel/UCVUvt1CeoZpCSnwg3oBMsOQ

----
Copyright © 2021 CircuitMess

Licensed under [GPLv3 License](https://www.gnu.org/licenses/gpl-3.0.html).
