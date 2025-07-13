#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Adafruit_MCP3008.h>

class ColorSensor {

  public:
    void init();
    void printReadings();
    void updateReadings();
    float getAvoidAngle();
    void printMappedValues();
};

#endif