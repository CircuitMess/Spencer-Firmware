#ifndef SPENCER_I2S_H
#define SPENCER_I2S_H
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"

class I2S {
  i2s_bits_per_sample_t BITS_PER_SAMPLE;
public:
  I2S();
  int Read(char* data, int numData);
  int GetBitPerSample();
};

#endif
