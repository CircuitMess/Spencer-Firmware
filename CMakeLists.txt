cmake_minimum_required(VERSION 3.15)
project(Spencer)
set(PORT /dev/ttyUSB0)
set(DEVICE cm:esp32:ringo)
set(CMAKE_CXX_STANDARD 11)

if(${WIN32} OR ${CYGWIN})
    set(Arduino15 $ENV{APPDATA}/../Local/Arduino15)
    set(ArduinoLibs $ENV{USERPROFILE}/Documents/Arduino/libraries)

    string(REPLACE "\\" "/" Arduino15 ${Arduino15})
    string(REPLACE "\\" "/" ArduinoLibs ${ArduinoLibs})

    if(${CYGWIN})
        string(REGEX REPLACE "^([A-Za-z]):" "/cygdrive/\\1" Arduino15 ${Arduino15})
        string(REGEX REPLACE "^([A-Za-z]):" "/cygdrive/\\1" ArduinoLibs ${ArduinoLibs})
    endif()
else()
    set(Arduino15 ~/.arduino15)
    set(ArduinoLibs ~/Arduino/libraries)
endif()

include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/libraries/Wire/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/libraries/FS/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/libraries/SD/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/libraries/SPI/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/libraries/WiFi/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/libraries/SPIFFS/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/libraries/HTTPClient/src)

include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/cores/esp32)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/tools/sdk)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/tools/sdk/include)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/esp32)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/freertos)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/driver)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/driver/driver)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.0.4/tools/sdk/include/spi_flash)

include_directories(${ArduinoLibs}/CircuitOS/src)
include_directories(${ArduinoLibs}/TFT_eSPI)
include_directories(${ArduinoLibs}/TFT_eSPI/Extensions)
include_directories(${ArduinoLibs}/ESP8266Audio/src)
include_directories(${ArduinoLibs}/SerialFlash)
include_directories(${ArduinoLibs}/ArduinoJson/src)


AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(src/DataStream SOURCES)
AUX_SOURCE_DIRECTORY(src/Intent SOURCES)
AUX_SOURCE_DIRECTORY(src/LEDmatrix SOURCES)
AUX_SOURCE_DIRECTORY(src/Services SOURCES)
AUX_SOURCE_DIRECTORY(src/Services/Audio SOURCES)
AUX_SOURCE_DIRECTORY(src/Services/TimeService SOURCES)
AUX_SOURCE_DIRECTORY(src/Speech SOURCES)
AUX_SOURCE_DIRECTORY(src/State SOURCES)
AUX_SOURCE_DIRECTORY(src/Util SOURCES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_definitions(-DDEBUG)
add_definitions(-DESP32)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_PROJECT_NAME}.ino PROPERTIES LANGUAGE CXX)

add_custom_command(OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf
        COMMAND arduino-cli compile --fqbn ${DEVICE} -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.ino
        DEPENDS ${CMAKE_PROJECT_NAME}.ino ${SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(CMBuild
        SOURCES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf)

add_custom_target(CMUpload ALL
        COMMAND arduino-cli upload --fqbn ${DEVICE} -p ${PORT} -i ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.bin
        DEPENDS CMBuild
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.ino ${SOURCES})