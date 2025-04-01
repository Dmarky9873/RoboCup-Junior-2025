#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#define NUM_CHANNELS 8
#define NUM_CHIPS 2

#include <Adafruit_MCP3008.h>

class ColorSensor {
  public:
    void init();
    void debugRaw();
    void debugFiltered();
    float getOOBDirection();

  private:
    int* getFilteredArr();
    int* getReadingsArr();
    int findArrayMidpoint(int* arr);
    Adafruit_MCP3008 chips[NUM_CHIPS];
};

#endif