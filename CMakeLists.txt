cmake_minimum_required(VERSION 3.15)
project(Spencer)

set(CMAKE_CXX_STANDARD 14)

include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/libraries/Wire/src)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/libraries/FS/src)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/libraries/SD/src)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/libraries/SPI/src)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/libraries/WiFi/src)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/libraries/SPIFFS/src)


include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/cores/esp32)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/tools/sdk)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/tools/sdk/include)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/esp32)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/freertos)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/driver)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/driver/driver)
include_directories(~/.arduino15/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/spi_flash)
include_directories(~/Arduino/libraries/NeoPixelBus/src)
include_directories(~/Arduino/libraries/CircuitOS/src)
include_directories(~/Arduino/libraries/ESP8266Audio/src)
include_directories(~/Arduino/libraries/SerialFlash-master)
include_directories(~/Arduino/libraries/Adafruit_Zero_I2S)

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(src/Services SOURCES)
AUX_SOURCE_DIRECTORY(src/Services/Audio SOURCES)
AUX_SOURCE_DIRECTORY(src/Util SOURCES)

add_definitions(-DDEBUG)

SET_SOURCE_FILES_PROPERTIES(Spencer.ino PROPERTIES LANGUAGE CXX)
add_executable(Spencer ${SOURCES} Spencer.ino)