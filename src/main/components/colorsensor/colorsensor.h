#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#define NUM_CHANNELS 8
#define NUM_CHIPS 2

#include <Adafruit_MCP3008.h>

class ColorSensor {
  public:
    void init();
    void printReadings();
    float isDetected();

  private:
    Adafruit_MCP3008 chips[NUM_CHIPS];
};

#endif